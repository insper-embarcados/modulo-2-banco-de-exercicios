/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <queue.h>


#include <stdio.h>
#include <string.h> 
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "hardware/irq.h"

const int BTN_PIN_A_1 = 28;
const int BTN_PIN_A_2 = 26;

const int BTN_PIN_B_1 = 21;
const int BTN_PIN_B_2 = 18;

const int LED_PIN_B = 8;
const int LED_PIN_Y = 13;

QueueHandle_t xQueueLEDn;
QueueHandle_t xQueueLED2;


void btn_callback(uint gpio, uint32_t events) {

    if (events & GPIO_IRQ_EDGE_FALL) {
        if ((gpio == 28) || (gpio == 26)) {
            int val = gpio - 26;
            xQueueSendFromISR(xQueueLEDn, &val, 0);
            if (val == 0)
             gpio_put(LED_PIN_B, 0);

        }
        else if ((gpio == 21) || (gpio == 18)) {
            int val = gpio - 18;
           // printf("val: %d\n", val);
            xQueueSendFromISR(xQueueLED2, &val, 0);
            if(val == 0){
                gpio_put(LED_PIN_Y, 0);
            }
        }
    }
}

void led_n_task(void* p) {

    gpio_init(LED_PIN_B);
    gpio_set_dir(LED_PIN_B, GPIO_OUT);

    int enable = 0;
    int status = 0;
    while (1) {
        if (xQueueReceive(xQueueLEDn, &enable, 0) == pdTRUE) {
            printf("1: %d\n", enable);
        }
        if (enable) {
            vTaskDelay(50);
            status = !status;
            gpio_put(LED_PIN_B, status);
        }
        else {
            gpio_put(LED_PIN_B, 0);
        }
    }
}


void led_2_task(void* p) {

    gpio_init(LED_PIN_Y);
    gpio_set_dir(LED_PIN_Y, GPIO_OUT);

    int enable = 0;
    int status = 0;
    while (1) {
        if (xQueueReceive(xQueueLED2, &enable, 0)  == pdTRUE) {
            printf("2: %d\n", enable);
        }

        if (enable) {
            vTaskDelay(50);
            status = !status;
            gpio_put(LED_PIN_Y, status);
        }
        else {
            gpio_put(LED_PIN_Y, 0);
        }
    }
}


// void btn_task(void* p) {


//     int gpio = 0;
//     while (true) {
//         if (xQueueReceive(xQueueBtn, &gpio, 100)) {
//             if (gpio == BTN_PIN_R)
//                 xSemaphoreGive(xSemaphoreLedR);
//             else
//                 xSemaphoreGive(xSemaphoreLedY);

//         }
//     }
// }


int main() {
    stdio_init_all();

    gpio_init(BTN_PIN_A_1);
    gpio_set_dir(BTN_PIN_A_1, GPIO_IN);
    gpio_pull_up(BTN_PIN_A_1);
    gpio_set_irq_enabled_with_callback(BTN_PIN_A_1,
        GPIO_IRQ_EDGE_FALL,
        true,
        &btn_callback);

    gpio_init(BTN_PIN_A_2);
    gpio_set_dir(BTN_PIN_A_2, GPIO_IN);
    gpio_pull_up(BTN_PIN_A_2);
    gpio_set_irq_enabled_with_callback(BTN_PIN_A_2,
        GPIO_IRQ_EDGE_FALL,
        true,
        &btn_callback);

    gpio_init(BTN_PIN_B_1);
    gpio_set_dir(BTN_PIN_B_1, GPIO_IN);
    gpio_pull_up(BTN_PIN_B_1);
    gpio_set_irq_enabled_with_callback(BTN_PIN_B_1,
        GPIO_IRQ_EDGE_FALL,
        true,
        &btn_callback);


    gpio_init(BTN_PIN_B_2);
    gpio_set_dir(BTN_PIN_B_2, GPIO_IN);
    gpio_pull_up(BTN_PIN_B_2);
    gpio_set_irq_enabled_with_callback(BTN_PIN_B_2,
        GPIO_IRQ_EDGE_FALL,
        true,
        &btn_callback);


    xQueueLEDn = xQueueCreate(32, sizeof(int));
    xQueueLED2 = xQueueCreate(32, sizeof(int));


    //xTaskCreate(btn_task, "BTN_Task 1", 256, NULL, 1, NULL);
    xTaskCreate(led_n_task, "LED_Task 1", 256, NULL, 1, NULL);
    xTaskCreate(led_2_task, "LED_Task 2", 256, NULL, 1, NULL);

    vTaskStartScheduler();

    while (1) {}

    return 0;
}
