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

#include "nrf_delay.h"
#include "nrf_error.h"
#include "app_uart.h"
#include "app_error.h"
#include "boards.h"
#include "write_app_uart.h"

#ifdef WRITE_TO_APP_UART

#define UART_TX_BUF_SIZE 128
#define UART_RX_BUF_SIZE 4

int _write(int fd, char * str, int len)
{
    for (int ii = 0; ii < len; ii++) {

        // We could try to do something clever here like
        // decide if the buffer is almost full and put
        // ... instead of running out of space and then
        // break out of the loop.

#if 1
        // TODO:
        // The example app uart code in SDK 8 does this
        // in a while loop like this. Not totally clear
        // why or what error they are expecting. Should
        // figure this out.

        unsigned count = 1000;

        while(app_uart_put(str[ii]) != NRF_SUCCESS) {
            if(!count--) {
                break;
            }
        }
#else
        // If no room in the buffer, just move on.
        app_uart_put(str[ii]);
#endif
    }

    return len;
}


static void uart_event_handle(app_uart_evt_t * p_event) {
    switch (p_event->evt_type) {
    case APP_UART_COMMUNICATION_ERROR:
    case APP_UART_FIFO_ERROR:
        // TODO - want to do anything for these errors?
        break;
    default:
        // Don't need to handle other events.
        break;
    }
}
#endif

uint32_t write_app_uart_init_with_pins(uint8_t rts_pin_number,
                                       uint8_t txd_pin_number,
                                       uint8_t cts_pin_number,
                                       uint8_t rxd_pin_number,
                                       bool hwfc) {

#ifdef WRITE_TO_APP_UART

    static bool already_initialized = false;

    if(already_initialized) {
        return NRF_ERROR_INVALID_STATE;
    }

    uint32_t err_code;

    const app_uart_comm_params_t comm_params = {
        rxd_pin_number,
        txd_pin_number,
        rts_pin_number,
        cts_pin_number,
        (hwfc ? APP_UART_FLOW_CONTROL_ENABLED : APP_UART_FLOW_CONTROL_DISABLED),
        false,
        UART_BAUDRATE_BAUDRATE_Baud38400
      };

    APP_UART_FIFO_INIT(&comm_params, UART_RX_BUF_SIZE, UART_TX_BUF_SIZE, uart_event_handle, APP_IRQ_PRIORITY_LOW, err_code);

    already_initialized = true;

    nrf_delay_ms(100);

    return err_code;
#else		
		return NRF_SUCCESS;
#endif
}
