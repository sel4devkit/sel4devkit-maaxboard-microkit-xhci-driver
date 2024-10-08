#
# Copyright 2021, Breakaway Consulting Pty. Ltd.
#
# SPDX-License-Identifier: BSD-2-Clause
#

# REQUIRED FOR FUNCTIONALITY
ifeq ($(strip $(BUILD_DIR)),)
$(error BUILD_DIR must be specified)
endif

ifeq ($(strip $(MICROKIT_TOOL)),)
$(error MICROKIT_TOOL must be specified)
endif

ifeq ($(strip $(MICROKIT_BOARD)),)
$(error MICROKIT_BOARD must be specified)
endif

ifeq ($(strip $(MICROKIT_CONFIG)),)
$(error MICROKIT_CONFIG must be specified)
endif

ifeq ($(strip $(NETBSD_DIR)),)
$(error NETBSD_DIR must be specified)
endif

# EXAMPLE EMPTY API USER

TOOLCHAIN_CLI := aarch64-none-elf
CC_CLIENT := $(COMPILER_PATH)/$(TOOLCHAIN_API)-gcc
LD_CLIENT := $(COMPILER_PATH)/$(TOOLCHAIN_CLI)-ld

LIBS_CLIENT := ${LIBC_DIR}/libgcc.a ${LIBC_DIR}/libc.a ${LIBC_DIR}/libm.a ${LIBC_DIR}/libgcc.a -lmicrokit -Tmicrokit.ld

# step 1: declare includes
# all of these includes are required for compilation of api
# feel free to add more here
CLIENT_INC := $(BOARD_DIR)/include api/include api/sDDF/include examples/empty-client/
CLIENT_INC_PARAMS=$(foreach d, $(CLIENT_INC), -I$d)

# step 2: declare compilation flags
# included here are the recommended compilation flags
CLIENT_CFLAGS := -mcpu=$(CPU) -mstrict-align  -nostdlib -nolibc -ffreestanding -g3 -O3 $(WARNINGS) $(CLIENT_INC_PARAMS) -I$(BOARD_DIR)/include --specs=${LIBC_DIR}/picolibc.specs

# step 3: declare linker flags
# the board library is required as a loader flag
CLIENT_LD_FLAGS := -L$(BOARD_DIR)/lib

# step 4: build xhci_api files
$(BUILD_DIR)/%.o: api/%.c Makefile
	$(CC_CLIENT) -c $(CLIENT_CFLAGS) $< -o $@

# step 5: build files required by client
$(BUILD_DIR)/%.o: examples/empty-client/%.c Makefile
	$(CC_CLIENT) -c $(CLIENT_CFLAGS) $< -o $@

# step 6: declare object files to include in elf file
# required files here are shared_ringbuffer and xhci_api. hidkbd map is a helper
# file for decoding keypresses
CLIENT_OBJS :=  empty-client.o hidkbdmap.o shared_queue.o shared_ringbuffer.o xhci_api.o

# step 7: compile elf
# This example includes libc. Note the *_OBJS is required to tell the compiler which
# o files to include.
$(BUILD_DIR)/example_client.elf: $(addprefix $(BUILD_DIR)/, $(CLIENT_OBJS))
	$(LD_CLIENT) $(CLIENT_LD_FLAGS) $^ ${LIBC_DIR}/libgcc.a ${LIBC_DIR}/libc.a ${LIBC_DIR}/libm.a ${LIBC_DIR}/libgcc.a $(LIBS_CLIENT) -o $@

# step 8: add elf file to list of images
# Use $(API_IMAGES) to reference driver required elfs compiled in its own makefile
IMAGES := $(API_IMAGES) example_client.elf

# step 9: build entire system
IMAGE_FILE = $(BUILD_DIR)/loader.img
REPORT_FILE = $(BUILD_DIR)/report.txt

all: $(IMAGE_FILE)
$(IMAGE_FILE) $(REPORT_FILE): $(addprefix $(BUILD_DIR)/, $(IMAGES)) examples/empty-client/empty-client.system
	$(MICROKIT_TOOL) examples/empty-client/empty-client.system --search-path $(BUILD_DIR) --board $(MICROKIT_BOARD) --config $(MICROKIT_CONFIG) -o $(IMAGE_FILE) -r $(REPORT_FILE)

# step 10: (optional) clean
clean:
	sudo rm -rf $(BUILD_DIR)
