#
# Copyright (c) 2014 Next Play Labs, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

TARGET_CHIP := NRF51822_QFAA_CA

#BOARD := BOARD_PCA10000
BOARD := BOARD_PCA10001

# Choose the log level of your choice.
#
# The options are:
#     CFLAGS += -DLOG_LEVEL=LOG_LEVEL_FATAL
#     CFLAGS += -DLOG_LEVEL=LOG_LEVEL_ERROR
#     CFLAGS += -DLOG_LEVEL=LOG_LEVEL_WARN
#     CFLAGS += -DLOG_LEVEL=LOG_LEVEL_INFO
#     CFLAGS += -DLOG_LEVEL=LOG_LEVEL_DEBUG
#     CFLAGS += -DLOG_LEVEL=LOG_LEVEL_TRACE
#
# or if you want to completely disable logging, e.g. for a
# production build,
#
#     CFLAGS += -DLOG_LEVEL=LOG_LEVEL_OFF
#
CFLAGS += -DLOG_LEVEL=LOG_LEVEL_DEBUG

C_SOURCE_FILES += main.c
C_SOURCE_FILES += log4nrf.c

C_SOURCE_FILES += simple_uart.c
C_SOURCE_FILES += nrf_delay.c

OUTPUT_FILENAME := log4nrf_demo

SDK_PATH = ../../../../

# Where is log4nrf? Since this is an example in nrfunit itself,
# it is right above us. In general it might be somewhere else.
LOG4NRF_DIR = ../..
C_SOURCE_PATHS += $(LOG4NRF_DIR)
INCLUDEPATHS += -I"$(LOG4NRF_DIR)"

INCLUDEPATHS += -I.

# These are standard Nordic include paths that go in most Makefiles
INCLUDEPATHS += -I"$(NPL_EMBED_SDK_ROOT)"

C_SOURCE_PATHS += $(NPL_EMBED_SDK_ROOT)

C_SOURCE_PATHS += $(SDK_PATH)Source/ble
C_SOURCE_PATHS += $(SDK_PATH)Source/ble/device_manager
C_SOURCE_PATHS += $(SDK_PATH)Source/app_common
C_SOURCE_PATHS += $(SDK_PATH)Source/sd_common

#Uncomment correct line if you have s110 programmed on the chip.
DEVICE_VARIANT := xxaa
#DEVICE_VARIANT := xxab

USE_SOFTDEVICE := S110
#USE_SOFTDEVICE := S210

LINKER_SCRIPT = gcc_$(DEVICESERIES)_s110_$(DEVICE_VARIANT).ld
OUTPUT_FILENAME := $(OUTPUT_FILENAME)_s110_$(DEVICE_VARIANT)

include $(SDK_PATH)Source/templates/gcc/Makefile.common
