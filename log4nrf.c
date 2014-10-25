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
#include "simple_uart.h"
#include "boards.h"

int _write(int fd, char * str, int len)
{
    for (int i = 0; i < len; i++)
    {
        simple_uart_put(str[i]);
    }
    return len;
}

void log4nrf_init_with_pins(uint8_t rts_pin_number,
                            uint8_t txd_pin_number,
                            uint8_t cts_pin_number,
                            uint8_t rxd_pin_number,
                            bool hwfc) {

    simple_uart_config(rts_pin_number, txd_pin_number, cts_pin_number, rxd_pin_number, hwfc);
    nrf_delay_ms(100);

    LOG_INFO("Logging initialized.");

}

void log4nrf_init() {

    log4nrf_init_with_pins(RTS_PIN_NUMBER, TX_PIN_NUMBER, CTS_PIN_NUMBER, RX_PIN_NUMBER, HWFC);
}
