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

# Change this if your SDK is in a differnt place.
SDK_PATH = /opt/local/nordic/sdk/nRF51_SDK_8.0.0_5fc2c3a

# Change this if your GNU ARM tools are in a different place.
GNU_INSTALL_ROOT = /opt/local/gcc-arm/gcc-arm-none-eabi-4_9-2014q4

# Send our printfs to the uart.
CFLAGS += -DWRITE_TO_APP_UART

DEVICE_VARIANT = xxac

SOFT_DEVICE_VERSION_NUM = 110
SOFT_DEVICE_VERSION = s$(SOFT_DEVICE_VERSION_NUM)

PROJECT_NAME = nrfunit_demo

export OUTPUT_FILENAME
#MAKEFILE_NAME := $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
MAKEFILE_NAME := $(MAKEFILE_LIST)
MAKEFILE_DIR := $(dir $(MAKEFILE_NAME) )

TEMPLATE_PATH = $(SDK_PATH)/components/toolchain/gcc
ifeq ($(OS),Windows_NT)
include $(TEMPLATE_PATH)/Makefile.windows
else
include $(TEMPLATE_PATH)/Makefile.posix
endif

MK := mkdir -p
RM := rm -rf

#echo suspend
ifeq ("$(VERBOSE)","1")
NO_ECHO :=
else
NO_ECHO := @
endif

# Toolchain commands
CC       		:= "$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-gcc"
AS       		:= "$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-as"
AR       		:= "$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-ar" -r
LD       		:= "$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-ld"
NM       		:= "$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-nm"
OBJDUMP  		:= "$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-objdump"
OBJCOPY  		:= "$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-objcopy"
SIZE    		:= "$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-size"

#function for removing duplicates in a list
remduplicates = $(strip $(if $1,$(firstword $1) $(call remduplicates,$(filter-out $(firstword $1),$1))))

# Our sources
C_SOURCE_FILES += ../all_tests.c
C_SOURCE_FILES += ../ts_example_basic.c
C_SOURCE_FILES += ../ts_example_another.c

DEVICE_SOURCE_FILES += ../device_main.c
DEVICE_SOURCE_FILES += ../../../nrfunit_device.c
DEVICE_SOURCE_FILES += ../../../write_app_uart.c

LOCAL_SOURCE_FILES += ../host_main.c

# SDK sources
SDK_SOURCE_FILES += $(SDK_PATH)/components/toolchain/system_nrf51.c
SDK_SOURCE_FILES += $(SDK_PATH)/components/drivers_nrf/hal/nrf_delay.c
SDK_SOURCE_FILES += $(SDK_PATH)/components/libraries/button/app_button.c
SDK_SOURCE_FILES += $(SDK_PATH)/components/drivers_nrf/uart/app_uart_fifo.c
SDK_SOURCE_FILES += $(SDK_PATH)/components/libraries/fifo/app_fifo.c
SDK_SOURCE_FILES += $(SDK_PATH)/components/libraries/gpiote/app_gpiote.c

#assembly files common to all targets
ASM_SOURCE_FILES  = $(SDK_PATH)/components/toolchain/gcc/gcc_startup_nrf51.s

#includes common to all targets
INC_PATHS  = -I../../..
INC_PATHS += -I$(SDK_PATH)/components/device
INC_PATHS += -I$(SDK_PATH)/components/toolchain
INC_PATHS += -I$(SDK_PATH)/components/toolchain/gcc
INC_PATHS += -I$(SDK_PATH)/components/libraries/button
INC_PATHS += -I$(SDK_PATH)/components/libraries/util
INC_PATHS += -I$(SDK_PATH)/components/libraries/scheduler
INC_PATHS += -I$(SDK_PATH)/components/libraries/fifo
INC_PATHS += -I$(SDK_PATH)/components/libraries/gpiote
INC_PATHS += -I$(SDK_PATH)/components/libraries/timer
INC_PATHS += -I$(SDK_PATH)/components/softdevice/$(SOFT_DEVICE_VERSION)/headers
INC_PATHS += -I$(SDK_PATH)/components/ble/common
INC_PATHS += -I$(SDK_PATH)/components/drivers_nrf/uart
INC_PATHS += -I$(SDK_PATH)/components/drivers_nrf/hal
INC_PATHS += -I$(SDK_PATH)/examples/bsp

OBJECT_DIRECTORY = _build
LISTING_DIRECTORY = $(OBJECT_DIRECTORY)
OUTPUT_BINARY_DIRECTORY = $(OBJECT_DIRECTORY)

SOFT_DEVICE_DIR = $(SDK_PATH)/components/softdevice/$(SOFT_DEVICE_VERSION)
SOFT_DEVICE_HEX = $(SOFT_DEVICE_DIR)/hex/$(SOFT_DEVICE_VERSION)_softdevice.hex

# Sorting removes duplicates
BUILD_DIRECTORIES := $(sort $(OBJECT_DIRECTORY) $(OUTPUT_BINARY_DIRECTORY) $(LISTING_DIRECTORY) )

#flags common to all targets
CFLAGS += -DNRF51
CFLAGS += -DBLE_STACK_SUPPORT_REQD
CFLAGS += -DS$(SOFT_DEVICE_VERSION_NUM)
CFLAGS += -DSOFTDEVICE_PRESENT
CFLAGS += -DBOARD_PCA10028
CFLAGS += -mcpu=cortex-m0
CFLAGS += -mthumb -mabi=aapcs --std=gnu99
CFLAGS += -Wall -Werror -O3
CFLAGS += -mfloat-abi=soft
# keep every function in separate section. This will allow linker to dump unused functions
CFLAGS += -ffunction-sections -fdata-sections -fno-strict-aliasing
CFLAGS += -flto -fno-builtin

# keep every function in separate section. This will allow linker to dump unused functions
LDFLAGS += -Xlinker -Map=$(LISTING_DIRECTORY)/$(OUTPUT_FILENAME).map
LDFLAGS += -mthumb -mabi=aapcs -L $(TEMPLATE_PATH) -T$(LINKER_SCRIPT)
LDFLAGS += -mcpu=cortex-m0
# let linker to dump unused sections
LDFLAGS += -Wl,--gc-sections
# use newlib in nano version
LDFLAGS += --specs=nano.specs -lc -lnosys

# Assembler flags
ASMFLAGS += -x assembler-with-cpp
ASMFLAGS += -DNRF51
ASMFLAGS += -DBLE_STACK_SUPPORT_REQD
ASMFLAGS += -DS$(SOFT_DEVICE_VERSION_NUM)
ASMFLAGS += -DSOFTDEVICE_PRESENT
ASMFLAGS += -DBOARD_PCA10028
#default target - first one defined
default: clean nrf51422_$(DEVICE_VARIANT)_$(SOFT_DEVICE_VERSION)

#building all targets
all: clean
	$(NO_ECHO)$(MAKE) -f $(MAKEFILE_NAME) -C $(MAKEFILE_DIR) -e cleanobj
	$(NO_ECHO)$(MAKE) -f $(MAKEFILE_NAME) -C $(MAKEFILE_DIR) -e nrf51422_$(DEVICE_VARIANT)_$(SOFT_DEVICE_VERSION)

#target for printing all targets
help:
	@echo following targets are available:
	@echo 	nrf51422_$(DEVICE_VARIANT)_$(SOFT_DEVICE_VERSION)

C_SOURCE_FILE_NAMES = $(notdir $(C_SOURCE_FILES))
C_PATHS = $(call remduplicates, $(dir $(C_SOURCE_FILES) ) )
C_OBJECTS = $(addprefix $(OBJECT_DIRECTORY)/, $(C_SOURCE_FILE_NAMES:.c=.o) )

SDK_SOURCE_FILE_NAMES = $(notdir $(SDK_SOURCE_FILES))
SDK_PATHS = $(call remduplicates, $(dir $(SDK_SOURCE_FILES) ) )
SDK_OBJECTS = $(addprefix $(OBJECT_DIRECTORY)/, $(SDK_SOURCE_FILE_NAMES:.c=.o) )

DEVICE_SOURCE_FILE_NAMES = $(notdir $(DEVICE_SOURCE_FILES))
DEVICE_PATHS = $(call remduplicates, $(dir $(DEVICE_SOURCE_FILES) ) )
DEVICE_OBJECTS = $(addprefix $(OBJECT_DIRECTORY)/, $(DEVICE_SOURCE_FILE_NAMES:.c=.o) )

ASM_SOURCE_FILE_NAMES = $(notdir $(ASM_SOURCE_FILES))
ASM_PATHS = $(call remduplicates, $(dir $(ASM_SOURCE_FILES) ))
ASM_OBJECTS = $(addprefix $(OBJECT_DIRECTORY)/, $(ASM_SOURCE_FILE_NAMES:.s=.o) )

vpath %.c $(call remduplicates, $(C_PATHS) $(SDK_PATHS) $(DEVICE_PATHS) $(LOCAL_PATHS))
vpath %.s $(ASM_PATHS)

NRF_OBJECTS = $(C_OBJECTS) $(SDK_OBJECTS) $(ASM_OBJECTS) $(DEVICE_OBJECTS)

HOST_OBJECTS = $(C_OBJECTS) $(LOCAL_OBJECTS)

OUTPUT_FILENAME=$(PROJECT_NAME)_$(DEVICE_VARIANT)_$(SOFT_DEVICE_VERSION)
LINKER_SCRIPT=gcc_nrf51_$(SOFT_DEVICE_VERSION)_$(DEVICE_VARIANT).ld

nrf51422_$(DEVICE_VARIANT)_$(SOFT_DEVICE_VERSION): $(BUILD_DIRECTORIES) $(NRF_OBJECTS)
	@echo Linking target: $(OUTPUT_FILENAME).out
	$(NO_ECHO)$(CC) $(LDFLAGS) $(NRF_OBJECTS) $(LIBS) -o $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out
	$(NO_ECHO)$(MAKE) -f $(MAKEFILE_NAME) -C $(MAKEFILE_DIR) -e finalize

## Create build directories
$(BUILD_DIRECTORIES):
	echo $(MAKEFILE_NAME)
	$(MK) $@

# Create objects from C SRC files
$(OBJECT_DIRECTORY)/%.o: %.c
	@echo Compiling file: $(notdir $<)
	$(NO_ECHO)$(CC) $(CFLAGS) $(INC_PATHS) -c -o $@ $<

# Assemble files
$(OBJECT_DIRECTORY)/%.o: %.s
	@echo Compiling file: $(notdir $<)
	$(NO_ECHO)$(CC) $(ASMFLAGS) $(INC_PATHS) -c -o $@ $<


# Link
$(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out: $(BUILD_DIRECTORIES) $(NRF_OBJECTS)
	@echo Linking target: $(OUTPUT_FILENAME).out
	$(NO_ECHO)$(CC) $(LDFLAGS) $(NRF_OBJECTS) $(LIBS) -o $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out


## Create binary .bin file from the .out file
$(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).bin: $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out
	@echo Preparing: $(OUTPUT_FILENAME).bin
	$(NO_ECHO)$(OBJCOPY) -O binary $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).bin

## Create binary .hex file from the .out file
$(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).hex: $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out
	@echo Preparing: $(OUTPUT_FILENAME).hex
	$(NO_ECHO)$(OBJCOPY) -O ihex $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).hex

.PHONY: finalize genbin genhex echosize

finalize: genbin genhex echosize

genbin:
	@echo Preparing: $(OUTPUT_FILENAME).bin
	$(NO_ECHO)$(OBJCOPY) -O binary $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).bin

## Create binary .hex file from the .out file
genhex:
	@echo Preparing: $(OUTPUT_FILENAME).hex
	$(NO_ECHO)$(OBJCOPY) -O ihex $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).hex

echosize:
	-@echo ""
	$(NO_ECHO)$(SIZE) $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out
	-@echo ""

program: genhex
	echo Programming $(BOARD)
	nrfjprog program -v -c $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).hex -s $(SOFT_DEVICE_HEX)

wipe:
	echo Wiping $(BOARD)
	nrfjprog wipe -v

clean:
	$(RM) $(BUILD_DIRECTORIES)


.PHONY: host_tests host_dirs

HOST_CC = gcc
HOST_CFLAGS = -std=c99 -g -Wall -Werror -I../../..
HOST_CPPFLAGS = -I./test -I. -I$(NPL_EMBED_SDK_ROOT) -I$(NRFUTILS_DIR) -DHOST_TESTING -DNRFUNIT_CONTINUE_ON_FAILURE

HOST_OBJDIR = $(OUTPUT_BINARY_DIRECTORY)/test-host/obj
HOST_BINDIR = $(OUTPUT_BINARY_DIRECTORY)/test-host/bin

LOCAL_SOURCE_FILE_NAMES = $(notdir $(LOCAL_SOURCE_FILES)) $(notdir $(C_SOURCE_FILES))
LOCAL_PATHS = $(call remduplicates, $(dir $(LOCAL_SOURCE_FILES) ) $(dir $(C_SOURCE_FILES) ) )
LOCAL_OBJECTS = $(addprefix $(HOST_OBJDIR)/, $(LOCAL_SOURCE_FILE_NAMES:.c=.o) )

HOST_TESTOBJS = $(LOCAL_OBJECTS)

HOST_TEST_BIN_NAME = host_$(PROJECT_NAME)
HOST_TEST_BIN = $(HOST_BINDIR)/$(HOST_TEST_BIN_NAME)

HOST_LDLIBS += -lm

HOST_COMPILE.c = $(HOST_CC) $(HOST_CFLAGS) $(HOST_CPPFLAGS) $(HOST_TARGET_ARCH) -c
HOST_LINK.c    = $(HOST_CC) $(HOST_CFLAGS) $(HOST_CPPFLAGS) $(HOST_LDFLAGS) $(HOST_TARGET_ARCH)

$(HOST_OBJDIR)/%.o: %.c
	@echo "HOST COMPILE " $@
	$Q$(HOST_COMPILE.c) $(OUTPUT_OPTION) $<

host_dirs: $(HOST_BINDIR) $(HOST_OBJDIR)

$(HOST_OBJDIR):
	$(MK) $@

$(HOST_BINDIR):
	$(MK) $@

host_tests: host_dirs $(HOST_TEST_BIN)

$(HOST_TESTOBJS):$(HOST_OBJDIR)

$(HOST_TEST_BIN):$(HOST_TESTOBJS)
	@echo "LINK    " $@
	$Q$(HOST_LINK.c) $(HOST_TESTOBJS) $(HOST_LDLIBS) $(OUTPUT_OPTION)




