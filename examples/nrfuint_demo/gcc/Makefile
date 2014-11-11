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

# These are files that contain the test suites. They will
# be compiled for both
TEST_C_SOURCE_FILES += ts_example_basic.c ts_example_another.c
TEST_C_SOURCE_FILES += all_tests.c

# These are files that will only be compiled when we are
# doing local testing on the host.
HOST_TEST_C_SOURCE_FILES += host_main.c

# These are files that will only be compiled when we are
# building tests to run on the device.
DEVICE_TEST_C_SOURCE_FILES += device_main.c
DEVICE_TEST_C_SOURCE_FILES += nrfunit_device.c
DEVICE_TEST_C_SOURCE_FILES += nrf_delay.c

DEVICE_TEST_C_SOURCE_FILES += log4nrf.c
DEVICE_TEST_C_SOURCE_FILES += simple_uart.c

# On the device, we need to compile and link all but the
# host code. To do this, we put them all in C_SOURCE_FILES
# and let Makefile.common take over from there.
C_SOURCE_FILES += $(TEST_C_SOURCE_FILES) $(DEVICE_TEST_C_SOURCE_FILES)

OUTPUT_FILENAME := nrfunit_demo
TEST_BIN_NAME = example_test
TESTSRCDIR = .

SDK_PATH = ../../../../../

# Where is nrfunit? Since this is an example in nrfunit itself,
# it is right above us. In general it might be somewhere else.
NRFUNIT_DIR = ../../..
C_SOURCE_PATHS += $(NRFUNIT_DIR)
INCLUDEPATHS += -I"$(NRFUNIT_DIR)"

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

.PHONY: allall

allall: all host_tests

include $(SDK_PATH)Source/templates/gcc/Makefile.common

HOST_TESTING = 1

include $(NRFUNIT_DIR)/Makefile.nrfunit
