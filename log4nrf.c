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

#include "log4nrf.h"

#include "nrf_delay.h"
#include "app_uart.h"
#include "app_error.h"
#include "boards.h"
#include "write_app_uart.h"

void log4nrf_init_with_pins(uint8_t rts_pin_number,
                            uint8_t txd_pin_number,
                            uint8_t cts_pin_number,
                            uint8_t rxd_pin_number,
                            bool hwfc) {

#if LOG_LEVEL > LOG_LEVEL_OFF

#ifndef WRITE_TO_APP_UART
#error WRITE_TO_APP_UART should be defined or writing to the UART will not work.
#endif

    write_app_uart_init_with_pins(rts_pin_number,
                                  txd_pin_number,
                                  cts_pin_number,
                                  rxd_pin_number,
                                  hwfc);

    LOG_INFO("Logging initialized.");
#endif
}

void log4nrf_init() {
    log4nrf_init_with_pins(RTS_PIN_NUMBER, TX_PIN_NUMBER, CTS_PIN_NUMBER, RX_PIN_NUMBER, HWFC);
}
