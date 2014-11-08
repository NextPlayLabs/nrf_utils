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

#ifndef LOG4NRF_H
#define LOG4NRF_H

#include <stdbool.h>
#include <inttypes.h>

// Logger macro API:
//
// On the compiler command line. e.g.
//
//     -DLOG_LEVEL=LOG_LEVEL_WARN
//
// sets logging level to WARN. In Nordic Makefile.common-derived Makefiles,
// this is done with
//
//     CFLAGS += -DLOG_LEVEL=LOG_LEVEL_WARN
//
// though a more standard use case would use CPPFLAGS since they apply to the
// preprocessor, not the compiler.
//
// In C code, include this header with
//
// #include "log4nrf.h"
//
// In your main, initialize logging before you do anything else, using
//
// int main(void)
// {
//     // Logging.
//     log4nrf_init();
//     ...
// }
//
//
// Now, anywhere else in your code, log (or don't depending on the level)
// using printf-style formatting with one of the following:
//
// LOG_FATAL(format, ...);
// LOG_ERROR(format, ...);
// LOG_WARN(format, ...);
// LOG_INFO(format, ...);
// LOG_DEBUG(format, ...);
// LOG_TRACE(format, ...);
//
// File name, line number, and log level will automatically be prepended, and
// "\r\n" will automatically be appended so you don't have to worry about it.
//
// Now suppose your code looks like:
//
// LOG_DEBUG("value = %d", value);
// if(value < 0) {
//     LOG_WARN("unexpected negative value %d", value);
// }
//
// and at runtime value = -2. Then if you compile with -DLOG_LEVEL=LOG_LEVEL_WARN,
// then your output will be
//
//     foo.c:42: WARN: unexpected negative value -2
//
// whereas if you compile with -DLOG_LEVEL=LOG_LEVEL_DEBUG you will get the output
//
//     foo.c:40: DEBUG: value = -2
//     foo.c:42: WARN: unexpected negative value -2
//
// The difference between the two is that setting the log level to LOG_LEVEL_DEBUG
// allowed debug log messages, and all higher levels, like warn, error, and fatal,
// to go through. Setting it to LOG_LEVEL_WARN lets WARN and higher through. Since
// DEBUG is not as severe at WARN, it is removed from the code and never executes.
//
// Of course, if the value is 4 at runtime, then with -DLOG_LEVEL=LOG_LEVEL_DEBUG
// you will get
//
//     foo.c:40: DEBUG: value = 4
//
// whereas with -DLOG_LEVEL=LOG_LEVEL_WARN you will get nothing in the log because
// the LOG_DEBUG will be disabled entirely.
//
// Having multiple levels is really useful. For example, for app error handling, we
// have a function like
//
//     void app_error_handler(uint32_terror_code, uint32_t line_num, const uint8_t * p_file_name) {
//
//         // Log the details of this fatal error before we reset the system.
//         LOG_FATAL("App error originally at %s:%u: error_code = 0x%08x",
//                   (char *)p_file_name, (unsigned)line_num, (unsigned)error_code);
//
//         NVIC_SystemReset();
//     }
//
// Even if we turn off all the other levels of logging by setting
// -DLOG_LEVEL=LOG_LEVEL_FATAL, so that we get no debug, info, warnings, etc... from
// the rest of our code, we will get a nice readable message in the log whenever we
// hit this code.
//

// We define these as macros so that the preprocessor
// has a chance to completely eliminate logging below
// the level we have chosen.
#define LOG_LEVEL_OFF       0
#define LOG_LEVEL_FATAL     1
#define LOG_LEVEL_ERROR     2
#define LOG_LEVEL_WARN      3
#define LOG_LEVEL_INFO      4
#define LOG_LEVEL_DEBUG     5
#define LOG_LEVEL_TRACE     6

// If not defined, it is off.
#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_OFF
#endif

#if LOG_LEVEL > LOG_LEVEL_OFF
#include <stdio.h>
#endif

// Macros for all of the different available levels. This enables logging
// code for all unused levels to be completely eliminated by the preprocessor.

#define __LOG_DO_ACTUAL_LOGGING(level, format, ...) printf("%s:%d: " level ": " format "\r\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define __LOG_NO_ACTUAL_LOGGING do {} while(0)

#if LOG_LEVEL >= LOG_LEVEL_FATAL
#define LOG_FATAL(format, ...) __LOG_DO_ACTUAL_LOGGING("FATAL", format, ##__VA_ARGS__)
#else
#define LOG_FATAL(format, ...) __LOG_NO_ACTUAL_LOGGING
#endif

#if LOG_LEVEL >= LOG_LEVEL_ERROR
#define LOG_ERROR(format, ...) __LOG_DO_ACTUAL_LOGGING("ERROR", format, ##__VA_ARGS__)
#else
#define LOG_ERROR(format, ...) __LOG_NO_ACTUAL_LOGGING
#endif

#if LOG_LEVEL >= LOG_LEVEL_WARN
#define LOG_WARN(format, ...) __LOG_DO_ACTUAL_LOGGING("WARN", format, ##__VA_ARGS__)
#else
#define LOG_WARN(format, ...) __LOG_NO_ACTUAL_LOGGING
#endif

#if LOG_LEVEL >= LOG_LEVEL_INFO
#define LOG_INFO(format, ...) __LOG_DO_ACTUAL_LOGGING("INFO", format, ##__VA_ARGS__)
#else
#define LOG_INFO(format, ...) __LOG_NO_ACTUAL_LOGGING
#endif

#if LOG_LEVEL >= LOG_LEVEL_DEBUG
#define LOG_DEBUG(format, ...) __LOG_DO_ACTUAL_LOGGING("DEBUG", format, ##__VA_ARGS__)
#else
#define LOG_DEBUG(format, ...) __LOG_NO_ACTUAL_LOGGING
#endif

#if LOG_LEVEL >= LOG_LEVEL_TRACE
#define LOG_TRACE(format, ...) __LOG_DO_ACTUAL_LOGGING("TRACE", format, ##__VA_ARGS__)
#else
#define LOG_TRACE(format, ...) __LOG_NO_ACTUAL_LOGGING
#endif



// Call this function right at the start of your main() to initialize
// the logging system so that logging is done via the SEGGER JLink.
// Output is at 38400 baud.
void log4nrf_init(void);

// Use this version if you would like to use specific pins other than
// the default pins defined in boards.h
void log4nrf_init_with_pins(uint8_t rts_pin_number,
                            uint8_t txd_pin_number,
                            uint8_t cts_pin_number,
                            uint8_t rxd_pin_number,
                            bool hwfc);

#endif
