#include "pico/stdlib.h"
#include "stdio.h"
#include "stdlib.h"

#define DEVICE_NAME "my-pico-device"
#define DEVICE_VRSN "v0.0.1"

const uint LED_PIN = 25;

main()
{
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while(1)
    {
        char symbol = getchar();
        printf("received char: %c [ ASCII code: %d ]\n", symbol, symbol);
        switch(symbol)
        {
        case 'e':
            gpio_put(LED_PIN, 1);
            printf("led enable done\n");
            break;

        case 'd':
            gpio_put(LED_PIN, 0);
            printf("led disable done\n");
            break;

        case 'v':
            printf(DEVICE_NAME);
            printf("\n");
            printf(DEVICE_VRSN);
            printf("\n");
            break;

        default:
            break;
        }
    }
}