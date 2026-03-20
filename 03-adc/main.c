#include "pico/stdlib.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdio-task/stdio-task.h"
#include "protocol-task/protocol-task.h"
#include "led-task/led-task.h"
#include "adc-task/adc-task.h"

#define DEVICE_NAME "my-pico-device"
#define DEVICE_VRSN "v0.0.1"

uint32_t global_variable = 0;

const uint32_t constant_variable = 42;

void version_callback(const char* args)
{
	printf("device name: '%s', firmware version: %s\n", DEVICE_NAME, DEVICE_VRSN);
}

void led_on_callback()
{
    led_task_state_set(1);
}

void led_off_callback()
{
    led_task_state_set(0);
}

void led_blink_callback()
{
    led_task_state_set(2);
}

void led_blink_set_period_ms_callback(char* args)
{
    uint32_t period_ms = 0;
    sscanf(args, "%u", &period_ms);
    if (!(period_ms))
    {
        printf("Error");
        return;
    }
    led_task_set_blink_period_ms(period_ms);
}

void help_callback();

void mem_callback(const char* args)
{
    uint32_t addr = 0;
    sscanf(args, "%x", &addr);
    
    if (addr == 0)
    {
        printf("Error\n");
        return;
    }
    
    uint32_t value = *(uint32_t*)addr;
    printf("%u \n", value);
}


void wmem_callback(const char* args)
{
    uint32_t addr = 0;
    uint32_t value = 0;
    sscanf(args, "%x %x", &addr, &value);

    if (addr == 0)
    {
        printf("Error\n");
        return;
    }
    
    *(uint32_t*)addr = value;
}

void get_adc_callback()
{
    float voltage_V = adc_task_handle();
    printf("%f\n", voltage_V);
}

void get_temp_callback()
{
    float temp_C = temp_task_handle();
    printf("%f\n", temp_C);
}

void tm_start_callback()
{
    adc_task_set_state(ADC_TASK_STATE_RUN);
}

void tm_stop_callback()
{
    adc_task_set_state(ADC_TASK_STATE_IDLE);
}

api_t device_api[] =
{
	{"version", version_callback, "get device name and firmware version"},
    {"on", led_on_callback, "led on"},
    {"off", led_off_callback, "led off"},
    {"blink", led_blink_callback, "led blink"},
    {"set_period", led_blink_set_period_ms_callback, "set period of led blink"},
    {"help", help_callback, "get description of commands"},
    {"mem", mem_callback, "read from memory"},
    {"wmem", wmem_callback, "write in memory"},
    {"get_adc", get_adc_callback, "get adc"},
    {"get_temp", get_temp_callback, "get temp"},
    {"tm_start", tm_start_callback, "start measurements"},
    {"tm_stop", tm_stop_callback, "stop measurements"},
	{NULL, NULL, NULL},
};

void help_callback()
{
    for (int i = 0; device_api[i].command_name; i++)
    {
        printf("Команда '");
        printf(device_api[i].command_name);
        printf("': '");
        printf(device_api[i].command_help);
        printf("'\n");
    }
}

main()
{
    stdio_init_all();
    stdio_task_init();
    protocol_task_init(device_api);
    led_task_init();
    adc_task_init();
    while(1)
    {
        char* command_name = stdio_task_handle();
        protocol_task_handle(command_name);
        led_task_handle();
        adc_task_handle();
    }
}