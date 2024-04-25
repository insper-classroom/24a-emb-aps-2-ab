#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <queue.h>

#include <string.h>

#include "pico/stdlib.h"
#include <stdio.h>


void init_buttons()
{
    gpio_init(BTN_PIN_RED);
    gpio_set_dir(BTN_PIN_RED, GPIO_IN);
    gpio_pull_up(BTN_PIN_RED);

    gpio_init(BTN_PIN_BLUE);
    gpio_set_dir(BTN_PIN_BLUE, GPIO_IN);
    gpio_pull_up(BTN_PIN_BLUE);

    gpio_init(BTN_PIN_GREEN);
    gpio_set_dir(BTN_PIN_GREEN, GPIO_IN);
    gpio_pull_up(BTN_PIN_GREEN);

    gpio_init(BTN_PIN_YELLOW);
    gpio_set_dir(BTN_PIN_YELLOW, GPIO_IN);
    gpio_pull_up(BTN_PIN_YELLOW);
}
