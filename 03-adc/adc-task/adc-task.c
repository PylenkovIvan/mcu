#include "hardware/adc.h"
#include "adc-task.h"
#include "stdio.h"
#include "stdlib.h"
#include "pico/stdlib.h"
#include "math.h"

const uint ADC_PIN = 26;
const uint ADC_CHANNEL = 0;
const uint TEMP_CHANNEL = 4;

void adc_task_init()
{
    adc_init();
    adc_gpio_init(ADC_PIN);
    adc_set_temp_sensor_enabled(true);
}

float adc_task_handle()
{
    adc_select_input(ADC_CHANNEL);
    uint16_t voltage_counts = adc_read();
    float voltage_V = voltage_counts * 3.3 / pow(2, 12);
    return voltage_V;
}

float temp_task_handle()
{
    adc_select_input(TEMP_CHANNEL);
    uint16_t voltage_counts = adc_read();
    float temp_V = voltage_counts * 3.3 / pow(2, 12);
    float temp_C = 27.0f - (temp_V - 0.706f) / 0.001721f;
    return temp_C;
}