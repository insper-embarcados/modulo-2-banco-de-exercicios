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

const int LED_PIN_B = 8;
const int LED_PIN_Y = 13;
const int LED_PIN_R = 22;


QueueHandle_t xQueueInput;

/**
 * NÃO MEXER!
 */
void input_task(void* p) {
    vTaskDelay(pdMS_TO_TICKS(350));
    int test_case;

    test_case = 5;
    xQueueSend(xQueueInput, &test_case, 0);

    test_case = 2;
    xQueueSend(xQueueInput, &test_case, 0);

    while (true) {
        vTaskDelay(portMAX_DELAY);
    }
}

/**
 * Seu código vem aqui!
 */



int main() {
    stdio_init_all();

    /**
     * manter essas duas linhas!
     */
    xQueueInput = xQueueCreate(32, sizeof(int));
    xTaskCreate(input_task, "Input", 256, NULL, 1, NULL);

    /**
     * Seu código vem aqui!
     */

    vTaskStartScheduler();

    while (1) {}

    return 0;
}