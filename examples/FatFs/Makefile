#
# Copyright 2021, Breakaway Consulting Pty. Ltd.
# Copyright 2022, UNSW (ABN 57 195 873 179)
#
# SPDX-License-Identifier: BSD-2-Clause
#

# Command to compile and run the img
#  make MICROKIT_BOARD=qemu_arm_virt MICROKIT_SDK=~/Sel4/libvmm-blk_benchmark/examples/blk_benchmark/sdk qemu



ifeq ($(strip $(MICROKIT_SDK)),)
$(error MICROKIT_SDK must be specified)
endif

ifeq ($(strip $(MICROKIT_BOARD)),)
$(error MICROKIT_BOARD must be specified)
endif

# Default build directory, pass BUILD_DIR=<dir> to override
# BUILD_DIR ?= build
# Default config is a debug build, pass CONFIG=<debug/release/benchmark> to override
CONFIG ?= debug

# @ivanv: Check for dependencies and make sure they are installed/in the path

# @ivanv: check that all dependencies exist
# Specify that we use bash for all shell commands
SHELL=/bin/bash
# All dependencies needed to compile the VMM
QEMU := qemu-system-aarch64
DTC := dtc

ifndef TOOLCHAIN
	# Get whether the common toolchain triples exist
	TOOLCHAIN_AARCH64_LINUX_GNU := $(shell command -v aarch64-linux-gnu-gcc 2> /dev/null)
	TOOLCHAIN_AARCH64_UNKNOWN_LINUX_GNU := $(shell command -v aarch64-unknown-linux-gnu-gcc 2> /dev/null)
	# Then check if they are defined and select the appropriate one
	ifdef TOOLCHAIN_AARCH64_LINUX_GNU
		TOOLCHAIN := aarch64-linux-gnu
	else ifdef TOOLCHAIN_AARCH64_UNKNOWN_LINUX_GNU
		TOOLCHAIN := aarch64-unknown-linux-gnu
	else
		$(error "Could not find an AArch64 cross-compiler")
	endif
endif

# CC_CLIENT := clang
# LD := ld.lld
TOOLCHAIN_CLI := aarch64-none-elf

CC_CLIENT := $(TOOLCHAIN_CLI)-gcc
LD_CLIENT := $(TOOLCHAIN_CLI)-ld
LIBS_CLIENT := ${LIBC_DIR}/libgcc.a ${LIBC_DIR}/libc.a ${LIBC_DIR}/libm.a ${LIBC_DIR}/libgcc.a -lmicrokit -Tmicrokit.ld
MICROKIT_TOOL ?= $(MICROKIT_SDK)/bin/microkit
SDDF := api/sDDF
SDDF_BLK_SHAREDQUEUE := $(SDDF)/blk/libblksharedqueue

# step 3: declare linker flags
# the board library is required as a loader flag
CLIENT_LD_FLAGS := -L$(BOARD_DIR)/lib

# File system building process
FF_DIR := api/sDDF/include/sddf/fs/fat

FatFs_OBJS :=   ff.o \
				ffsystem.o \
				ffunicode.o \
                AsyncFATFs.o \
				AsyncFATFunc.o \
				Asyncdiskio.o \
				fs_shared_queue.o \
				shared_queue.o \
				FiberPool.o \
				FiberFlow.o \
				# util.o \

# $(BUILD_DIR)/shared_queue.o: Makefile
# 	$(MAKE) -C $(SDDF_BLK_SHAREDQUEUE) MICROKIT_INCLUDE=$(MICROKIT_SDK)
# 	cp $(SDDF_BLK_SHAREDQUEUE)/shared_queue.o $(BUILD_DIR)/shared_queue.o

# CFLAGS_T := \
# 	-mstrict-align \
# 	-ffreestanding \
# 	-g \
# 	-O0 \
# 	-Wall \
# 	-Wno-unused-function \
# 	-target aarch64-none-elf \
# 	-no-integrated-as \

# $(BUILD_DIR)/musllibc/lib/libc.a:
# 	make -C $(MUSL) \
# 		C_COMPILER=$(CC_CLIENT) \
# 		TOOLPREFIX="" \
# 		CONFIG_ARCH_AARCH64=y \
# 		CONFIG_USER_DEBUG_BUILD=y \
# 		STAGE_DIR=$(abspath $(BUILD_DIR)/musllibc) \
# 		CFLAGS="-mstrict-align -ffreestanding -g -O0 -Wall -Wno-unused-function -target aarch64-none-elf -no-integrated-as" \
# 		SOURCE_DIR=.
		
CLIENT_INC := $(BOARD_DIR)/include api/include api/sDDF/include api/sDDF/include/fs/fat
CLIENT_INC_PARAMS=$(foreach d, $(CLIENT_INC), -I$d)

# step 2: declare compilation flags
# included here are the recommended compilation flags
CLIENT_CFLAGS := -mcpu=$(CPU) -mstrict-align  -nostdlib -nolibc -ffreestanding -g3 -O3 $(WARNINGS) $(CLIENT_INC_PARAMS) --specs=${LIBC_DIR}/picolibc.specs

$(BUILD_DIR)/%.o: $(FF_DIR)/ff15/source/%.c Makefile
	$(CC_CLIENT) -c $(CLIENT_CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: $(FF_DIR)/%.c Makefile
	$(CC_CLIENT) -c $(CLIENT_CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: $(FF_DIR)/FiberPool/%.c Makefile
	$(CC_CLIENT) -c $(CLIENT_CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: $(FF_DIR)/FiberPool/FiberFlow/%.c Makefile
	$(CC_CLIENT) -c $(CLIENT_CFLAGS) $< -o $@

$(BUILD_DIR)/fs_shared_queue.o: $(FF_DIR)/libfssharedqueue/fs_shared_queue.c Makefile
	$(CC_CLIENT) -c $(CLIENT_CFLAGS) $< -o $@

$(BUILD_DIR)/FatFs.elf: $(addprefix $(BUILD_DIR)/, $(FatFs_OBJS))
	$(LD_CLIENT) $(CLIENT_LD_FLAGS) $^ $(LIBS_CLIENT) -o $@
# File system building end

# Client building process
Client_OBJS :=  FS_testclient.o \
				fs_shared_queue.o \
				FiberPool.o \
				FiberFlow.o \
				libfatfs.o \

$(BUILD_DIR)/FS_testclient.o: examples/FatFs/FS_testclient.c Makefile
	$(CC_CLIENT) -c $(CLIENT_CFLAGS) $< -o $@

$(BUILD_DIR)/libfatfs.o: examples/FatFs/libfatfs.c Makefile
	$(CC_CLIENT) -c $(CLIENT_CFLAGS) $< -o $@

$(BUILD_DIR)/Client.elf: $(addprefix $(BUILD_DIR)/, $(Client_OBJS))
	$(LD_CLIENT) $(CLIENT_LD_FLAGS) $^ $(LIBS_CLIENT) -o $@
# Client building end


IMAGES := $(API_IMAGES) Client.elf FatFs.elf

# step 9: build entire system
IMAGE_FILE = $(BUILD_DIR)/loader.img
REPORT_FILE = $(BUILD_DIR)/report.txt

all: $(IMAGE_FILE)
$(IMAGE_FILE) $(REPORT_FILE): $(addprefix $(BUILD_DIR)/, $(IMAGES)) examples/shell/shell.system
	$(MICROKIT_TOOL) examples/FatFs/FatFs.system --search-path $(BUILD_DIR) --board $(MICROKIT_BOARD) --config $(MICROKIT_CONFIG) -o $(IMAGE_FILE) -r $(REPORT_FILE)

# step 10: (optional) clean
clean:
	sudo rm -rf $(BUILD_DIR)