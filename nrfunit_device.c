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

#include <stdbool.h>
#include "nrf.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "boards.h"
#include "nrfunit.h"
#include "nrfunit_device.h"

// Support for running nrfunit tests on the NRF51822 device.
// To use this, call nrf_nrfunit_init() at the beggining
// of your main. It will grab LED_0  and LED_1 for it's own use,
// and initialize button inputs. It will not initialize or start
// anything else on the device.
//
// Next, do any other initialization, then call
// nrf_nrfunit_main_loop(), which will never return.
//
// To invoke your actual tests, link in a function
//
//     const char *all_tests()
//
// of your own, which nrf_nrfunit_main_loop() will call.


// We begin by defining the counters that keep track of how many
// tests we have run. These were declared in nrfunit.h so they
// are known to all test files.
unsigned test_suites_run;
unsigned tests_run;
unsigned asserts_run;
unsigned asserts_failed;

void nrfunit_device_init() {

    // Configure LED-pins as outputs
    nrf_gpio_cfg_output(LED_0);
    nrf_gpio_cfg_output(LED_1);

    // Configure the buttons as inputs.
    nrf_gpio_range_cfg_input(BUTTON_START, BUTTON_STOP, BUTTON_PULL);
}


void nrfunit_device_main_loop() {

    while (true) {

        printf("\n\r\n\r");

        test_suites_run = 0;
        tests_run = 0;
        asserts_run = 0;
        asserts_failed = 0;

        // Turn on LED_0 to indicate we are ready
        // to start tests.

        nrf_gpio_pin_clear(LED_1);
        nrf_gpio_pin_set(LED_0);

        // Wait for a button press to start running
        // the test.

        uint8_t button_pushed = 0;

        // Wait for the button to be pushed.
        while(!button_pushed) {
            button_pushed = !nrf_gpio_pin_read(BUTTON_0);
        }

        // Both LEDs now on.
        nrf_gpio_pin_set(LED_1);

        // Wait for it to be released.
        while(button_pushed) {
            button_pushed = !nrf_gpio_pin_read(BUTTON_0);
        }

        // Now just one LED.
        nrf_gpio_pin_clear(LED_0);

        // Now run the test suite.

        const char *result = all_tests();

        // Print a summary of the results.

#if NRFUNIT_CONTINUE_ON_FAILURE
        if (asserts_failed) {
            printf("%u of %u asserts failed in %u tests and %u test suites.\n", asserts_failed, asserts_run, tests_run, test_suites_run);
        } else {
            printf("%u asserts passed in %u tests and %u test suites.\n", asserts_run, tests_run, test_suites_run);
        }
#else
        if (result != 0) {
            printf("%s\n", result);
        } else {
            printf("ALL TESTS PASSED\n");
        }

        printf("%u asserts run in %u tests and %u test suites.\n", asserts_run, tests_run, test_suites_run);
#endif

        if(asserts_failed || result != 0) {

            // We failed, so before we go back to let the tests start
            // again, blink the LEDs until the button is pushed
            // and released.

            // Blink and wait for the button to be pushed.
            // Pretty lousy way to do this without timers, but
            // we want to avoid touching as many chip resources
            // as possible.
            while(!button_pushed) {

                button_pushed = nrf_gpio_pin_read(BUTTON_0);

                nrf_gpio_pin_clear(LED_1);
                nrf_gpio_pin_set(LED_0);

                nrf_delay_ms(200);

                button_pushed |= nrf_gpio_pin_read(BUTTON_0);

                nrf_gpio_pin_clear(LED_0);
                nrf_gpio_pin_set(LED_1);

                nrf_delay_ms(200);

                button_pushed |= nrf_gpio_pin_read(BUTTON_0);
            }

            nrf_gpio_pin_clear(LED_0);
            nrf_gpio_pin_clear(LED_1);

            // Wait for the button to be released.
            while(button_pushed) {
                button_pushed = nrf_gpio_pin_read(BUTTON_0);
            }
        }
    }
}

