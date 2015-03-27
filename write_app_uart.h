/*
 * Copyright (c) 2015 Next Play Labs, Inc.
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
#ifndef WRITE_APP_UART_H
#define WRITE_APP_UART_H

#include <inttypes.h>

uint32_t write_app_uart_init_with_pins(uint8_t rts_pin_number,
                                       uint8_t txd_pin_number,
                                       uint8_t cts_pin_number,
                                       uint8_t rxd_pin_number,
                                       bool hwfc);

#endif
