#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <queue.h>

#include <string.h>

#include "pico/stdlib.h"
#include <stdio.h>

#include "hc05.h"
#include "periferics.h"

QueueHandle_t xQueueButPressed;

const int BTN_PIN_RED = 6;
const int BTN_PIN_BLUE = 7;
const int BTN_PIN_GREEN = 8;
const int BTN_PIN_YELLOW = 9;

void btn_callback(uint gpio, uint32_t events)
{
    if(gpio == BTN_PIN_RED)
    {
        char button = 'r';
        xQueueSendFromISR(xQueueButPressed, &button, 0);
    }
    else if(gpio == BTN_PIN_BLUE)
    {
        char button = 'b';
        xQueueSendFromISR(xQueueButPressed, &button, 0);
    }
    else if(gpio == BTN_PIN_GREEN)
    {
        char button = 'g';
        xQueueSendFromISR(xQueueButPressed, &button, 0);
    }
    else if(gpio == BTN_PIN_YELLOW)
    {
        char button = 'y';
        xQueueSendFromISR(xQueueButPressed, &button, 0);
    }
}

void hc05_task(void *p)
{
    uart_init(hc05_UART_ID, hc05_BAUD_RATE);
    gpio_set_function(hc05_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(hc05_RX_PIN, GPIO_FUNC_UART);
    hc05_init("SNAKE", "1234");

    char button;
    while (true)
    {
        if( xQueueReceive(xQueueButPressed, &button, 1))
        {
            // printf("button: %c\n", button);
            if (button == 'r')
            {
                uart_puts(hc05_UART_ID, "r");
                uart_putc_raw(uart0, -1);
            }
            else if (button == 'b')
            {
                uart_puts(hc05_UART_ID, "b");
                uart_putc_raw(uart0, -1);
            }
            else if (button == 'g')
            {
                uart_puts(hc05_UART_ID, "g");
                uart_putc_raw(uart0, -1);
            }
            else if (button == 'y')
            {
                uart_puts(hc05_UART_ID, "y");
                uart_putc_raw(uart0, -1);
            }
            vTaskDelay(pdMS_TO_TICKS(100));
        }
    }
}

int main()
{
    stdio_init_all();
    xQueueButPressed = xQueueCreate(32, sizeof(char) );
    init_buttons();

    printf("Start bluetooth task\n");
    xTaskCreate(hc05_task, "UART_Task 1", 4096, NULL, 1, NULL);

    vTaskStartScheduler();

    while (true);
}


void init_buttons()
{
    gpio_set_irq_enabled_with_callback(BTN_PIN_RED, GPIO_IRQ_EDGE_FALL, true, &btn_callback);
    gpio_init(BTN_PIN_RED);
    gpio_set_dir(BTN_PIN_RED, GPIO_IN);
    gpio_pull_up(BTN_PIN_RED);

    gpio_set_irq_enabled(BTN_PIN_BLUE, GPIO_IRQ_EDGE_FALL, true);
    gpio_init(BTN_PIN_BLUE);
    gpio_set_dir(BTN_PIN_BLUE, GPIO_IN);
    gpio_pull_up(BTN_PIN_BLUE);

    gpio_set_irq_enabled(BTN_PIN_GREEN, GPIO_IRQ_EDGE_FALL, true);
    gpio_init(BTN_PIN_GREEN);
    gpio_set_dir(BTN_PIN_GREEN, GPIO_IN);
    gpio_pull_up(BTN_PIN_GREEN);

    gpio_set_irq_enabled(BTN_PIN_YELLOW, GPIO_IRQ_EDGE_FALL, true);
    gpio_init(BTN_PIN_YELLOW);
    gpio_set_dir(BTN_PIN_YELLOW, GPIO_IN);
    gpio_pull_up(BTN_PIN_YELLOW);
}


// void hc06_task(void *p) {
//     uart_init(HC06_UART_ID, HC06_BAUD_RATE);
//     gpio_set_function(HC06_TX_PIN, GPIO_FUNC_UART);
//     gpio_set_function(HC06_RX_PIN, GPIO_FUNC_UART);
//     hc06_init("DINO", "1234");
// }
