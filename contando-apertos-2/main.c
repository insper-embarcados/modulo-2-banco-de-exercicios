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

int main() {
    stdio_init_all();

    vTaskStartScheduler();
    while (1) {
    }
    return 0;
}
