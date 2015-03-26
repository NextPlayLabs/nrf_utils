/*
 * Copyright (c) 2014 Next Play Labs, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "nordic_common.h"
#include "nrf.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "bsp.h"

#include "log4nrf.h"



void example_init() {

    // Configure LED-pins as outputs
    nrf_gpio_cfg_output(BSP_LED_0);
    nrf_gpio_cfg_output(BSP_LED_1);

    // Configure the buttons as inputs.
    nrf_gpio_range_cfg_input(BUTTON_START, BUTTON_STOP, BUTTON_PULL);
}


int main(int argc, char **argv) {

    // Initialize logging on the board's default UART pins.
    log4nrf_init();

    example_init();

    // Here is how to invoke logging at different levels.
    // Look in the Makefile and change the
    //
    //     CFLAGS += -DLOG_LEVEL=LOG_LEVEL_*
    //
    // line to select different levels and see how it affects
    // the following log statements. Note that when you select
    // a level, all more severe levels are also enabled. so,
    // for example. if you set
    //
    //     CFLAGS += -DLOG_LEVEL=LOG_LEVEL_INFO
    //
    // then you will see output from calls to LOG_INFO(), LOG_WARN(),
    // LOG_ERROR(), and LOG_FATAL(), but no output from LOG_DEBUG()
    // or LOG_TRACE(), which are less severe.
    //
    // (When Keil is used, open Target Options (Alt+F7) and go to the C/C++ tab.
    // In the list of defines, change LOG_LEVEL to the desired level.)

    LOG_TRACE("Trace logging is on.");
    LOG_DEBUG("Debug logging is on.");
    LOG_INFO("Info logging is on.");
    LOG_WARN("Warn logging is on.");
    LOG_ERROR("Error logging is on.");
    LOG_FATAL("Fatal logging is on.");

    // Notice that we can format log messages as we like
    // using printf() formatting conventions.
    LOG_INFO("We can format %s or numbers like 0x%08x and %d in our log messages, just like printf(format, ...)",
             "strings", 0xABCDEF, 12345);

    // In this loop we simply wait for the user to push
    // and release buttons. When they do, we log the events
    // at the debug level. Depending on whether the program
    // is compiled with a level of logging that captures
    // debug events, we will or will not see logging here.

    while(true) {

        // Set one of the LEDs and clear the other.
        nrf_gpio_pin_clear(BSP_LED_1);
        nrf_gpio_pin_set(BSP_LED_0);

        uint8_t button_pushed = 0;

        LOG_DEBUG("Waiting for the user to hit a button...");

        while(!button_pushed) {
            button_pushed = !nrf_gpio_pin_read(BSP_BUTTON_0);
        }

        // Toggle the LEDs.
        nrf_gpio_pin_clear(BSP_LED_0);
        nrf_gpio_pin_set(BSP_LED_1);

        LOG_DEBUG("Button pushed.");

        while(button_pushed) {
            button_pushed = !nrf_gpio_pin_read(BSP_BUTTON_0);
        }

        LOG_DEBUG("Button released.");
    }
}
