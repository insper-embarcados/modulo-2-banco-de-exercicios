/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <FreeRTOS.h>
#include <queue.h>
#include <semphr.h>
#include <stdio.h>
#include <string.h>
#include <task.h>

#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "pico/stdlib.h"

const int BTN_PIN_G = 28;
const int BTN_PIN_Y = 26;

const int LED_PIN_G = 5;
const int LED_PIN_Y = 9;
const int LED_PIN_R = 13;

volatile int btn_f = 0;
volatile int g_timer_g = 0;
volatile int g_timer_y = 0;
volatile int g_timer_r = 0;
volatile int g_fired_g = 0;
volatile int g_fired_y = 0;

SemaphoreHandle_t xSemaphoreLedG;
SemaphoreHandle_t xSemaphoreLedY;
QueueHandle_t xQueueValue;

void btn_callback(uint gpio, uint32_t events) {
    if (events == 0x4) {  // fall edge
        btn_f = gpio;
        if (gpio == BTN_PIN_G) {
            xSemaphoreGiveFromISR(xSemaphoreLedG, 0);
        } else if (gpio == BTN_PIN_Y)
            xSemaphoreGiveFromISR(xSemaphoreLedY, 0);

    } else if (events == 0x8) {  // rise edge
    }
}

void led_task(void* p) {
    int value = 0;
    while (true) {
        if (xQueueReceive(xQueueValue, &value, 0)) {
            for (int i = 0; i < value; i++) {
                gpio_put(LED_PIN_G, 1);
                vTaskDelay(pdMS_TO_TICKS(250));
                gpio_put(LED_PIN_G, 0);
                vTaskDelay(pdMS_TO_TICKS(250));
            }
        }
    }
}

void process_task(void* p) {
    int value = 0;
    while (true) {
        if (xSemaphoreTake(xSemaphoreLedY, 10)) {
            value = 10;
            xQueueSend(xQueueValue, &value, 0);
        }

        if (xSemaphoreTake(xSemaphoreLedG, 10)) {
            value = 5;
            xQueueSend(xQueueValue, &value, 0);
        }
    }
}

int main() {
    stdio_init_all();

    /**
     * manter essas linhas
     */
    xSemaphoreLedG = xSemaphoreCreateBinary();
    xSemaphoreLedY = xSemaphoreCreateBinary();
    xQueueValue = xQueueCreate(10, sizeof(int));

    gpio_init(BTN_PIN_G);
    gpio_set_dir(BTN_PIN_G, GPIO_IN);
    gpio_pull_up(BTN_PIN_G);
    gpio_set_irq_enabled_with_callback(BTN_PIN_G, GPIO_IRQ_EDGE_FALL, true,
                                       &btn_callback);

    gpio_init(BTN_PIN_Y);
    gpio_set_dir(BTN_PIN_Y, GPIO_IN);
    gpio_pull_up(BTN_PIN_Y);
    gpio_set_irq_enabled_with_callback(BTN_PIN_Y, GPIO_IRQ_EDGE_FALL, true,
                                       &btn_callback);

    gpio_init(LED_PIN_G);
    gpio_set_dir(LED_PIN_G, GPIO_OUT);

    gpio_init(LED_PIN_Y);
    gpio_set_dir(LED_PIN_Y, GPIO_OUT);

    xTaskCreate(led_task, "g_task", 256, NULL, 2, NULL);
    xTaskCreate(process_task, "y_task", 256, NULL, 2, NULL);

    /**
     * Seu código vem aqui!
     */

    vTaskStartScheduler();

    while (1) {
    }

    return 0;
}