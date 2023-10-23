#
# Copyright 2021, Breakaway Consulting Pty. Ltd.
#
# SPDX-License-Identifier: BSD-2-Clause
#
ifeq ($(strip $(BUILD_DIR)),)
$(error BUILD_DIR must be specified)
endif

ifeq ($(strip $(MICROKIT_SDK)),)
$(error MICROKIT_SDK must be specified)
endif

ifeq ($(strip $(MICROKIT_BOARD)),)
$(error MICROKIT_BOARD must be specified)
endif

ifeq ($(strip $(MICROKIT_CONFIG)),)
$(error MICROKIT_CONFIG must be specified)
endif

ifeq ($(strip $(MICROKIT_DIR)),)
$(error MICROKIT_DIR must be specified)
endif

ifeq ($(strip $(NETBSD_DIR)),)
$(error NETBSD_DIR must be specified)
endif

TOOLCHAIN := aarch64-none-elf

CPU := cortex-a53

CC := $(TOOLCHAIN)-gcc
LD := $(TOOLCHAIN)-ld
AS := $(TOOLCHAIN)-as
MICROKIT_TOOL ?= $(MICROKIT_SDK)/bin/microkit

# NETBSD_SRC			:=  dev_verbose.o subr_device.o subr_autoconf.o usbdi_util.o usbdi.o usbroothub.o sel4_bus_funcs.o dma.o usb.o usb_quirks.o usb_subr.o xhci.o usb_mem.o uhub.o hid.o uhidev.o ukbd.o ums.o uts.o hidms.o hidkbdmap.o ioconf.o tpcalib.o uhid.o
NETBSD_SRC			:=  dev_verbose.o subr_device.o subr_autoconf.o usbdi_util.o usbdi.o usbroothub.o sel4_bus_funcs.o dma.o usb.o usb_quirks.o usb_subr.o xhci.o usb_mem.o uhub.o hid.o uhidev.o ukbd.o ums.o uts.o hidms.o hidkbdmap.o ioconf.o tpcalib.o uhid.o umass.o umass_quirks.o # umass_scsipi.o scsipi_base.o scsipiconf.o scsiconf.o scsi_subr.o # scsipi_ioctl.o # ugen.o tty_subr.o kern_event.o sys_select.o //not implemented yet
UTILS				:= 	tinyalloc.o printf.o util.o timer.o

XHCI_STUB_OBJS 		:=  xhci_stub.o $(NETBSD_SRC) imx8mq_usbphy.o dwc3_fdt.o shared_ringbuffer.o $(UTILS)
SOFTWARE_OBJS 		:=  software_interrupts.o $(NETBSD_SRC) imx8mq_usbphy.o dwc3_fdt.o $(UTILS) shared_ringbuffer.o
HARDWARE_OBJS 		:=  hardware_interrupts.o sel4_bus_funcs.o $(UTILS)
MEM_OBJS			:=  mem_handler.o tinyalloc.o printf.o
KBD_LOGGER_OBJS 	:=  kbd_logger.o hidkbdmap.o shared_ringbuffer.o printf.o tinyalloc.o
SIMULATED_KBD_OBJS	:=  simulated_kbd.o printf.o tinyalloc.o

BOARD_DIR := $(MICROKIT_SDK)/board/$(MICROKIT_BOARD)/$(MICROKIT_CONFIG)

IMAGES := xhci_stub.elf hardware.elf software.elf mem_handler.elf kbd_logger.elf simulated_kbd.elf
INC := $(BOARD_DIR)/include include/tinyalloc include/wrapper $(NETBSD_DIR)/sys $(NETBSD_DIR)/mach_include include/bus include/dma include/printf include/timer src/
INC_PARAMS=$(foreach d, $(INC), -I$d)
WARNINGS := -Wall -Wno-comment -Wno-return-type -Wno-unused-function -Wno-unused-value -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-label -Wno-pointer-sign
CFLAGS := -mcpu=$(CPU) -mstrict-align -ffreestanding -g3 -O3 $(WARNINGS) $(INC_PARAMS) -I$(BOARD_DIR)/include -DSEL4  -DSEL4_USB_DEBUG
LDFLAGS := -L$(BOARD_DIR)/lib
LIBS := -lmicrokit -Tmicrokit.ld

IMAGE_FILE = $(BUILD_DIR)/loader.img
REPORT_FILE = $(BUILD_DIR)/report.txt

all: includes

all: $(IMAGE_FILE)

includes:
	@mkdir -p ${NETBSD_DIR}/mach_include/machine
	@ln -fs ${NETBSD_DIR}/sys/arch/evbarm/include/* $(NETBSD_DIR)/mach_include/machine/
	@mkdir -p ${NETBSD_DIR}/mach_include/arm
	@ln -fs ${NETBSD_DIR}/sys/arch/arm/include/* $(NETBSD_DIR)/mach_include/arm/
	@mkdir -p ${NETBSD_DIR}/mach_include/aarch64
	@ln -fs ${NETBSD_DIR}/sys/arch/arm/include/* $(NETBSD_DIR)/mach_include/aarch64/

$(BUILD_DIR)/%.o: src/%.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: cap/%.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/usb.o: $(NETBSD_DIR)/sys/dev/usb/usb.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/usbdi.o: $(NETBSD_DIR)/sys/dev/usb/usbdi.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/usbdi_util.o: $(NETBSD_DIR)/sys/dev/usb/usbdi_util.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/usb_mem.o: $(NETBSD_DIR)/sys/dev/usb/usb_mem.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/usb_quirks.o: $(NETBSD_DIR)/sys/dev/usb/usb_quirks.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/usb_subr.o: $(NETBSD_DIR)/sys/dev/usb/usb_subr.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/usbroothub.o: $(NETBSD_DIR)/sys/dev/usb/usbroothub.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/umass.o: netbsd/src/sys/dev/usb/umass.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/umass_scsipi.o: netbsd/src/sys/dev/usb/umass_scsipi.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/umass_quirks.o: netbsd/src/sys/dev/usb/umass_quirks.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/scsiconf.o: netbsd/src/sys/dev/scsipi/scsiconf.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/scsi_subr.o: netbsd/src/sys/dev/scsipi/scsi_subr.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@
	
$(BUILD_DIR)/scsipi_base.o: netbsd/src/sys/dev/scsipi/scsipi_base.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/scsipiconf.o: netbsd/src/sys/dev/scsipi/scsipiconf.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

# $(BUILD_DIR)/scsipi_ioctl.o: netbsd/src/sys/dev/scsipi/scsipi_ioctl.c Makefile
# 	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/uts.o: $(NETBSD_DIR)/sys/dev/usb/uts.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/uhid.o: $(NETBSD_DIR)/sys/dev/usb/uhid.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/uhidev.o: $(NETBSD_DIR)/sys/dev/usb/uhidev.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/uhub.o: $(NETBSD_DIR)/sys/dev/usb/uhub.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/ukbd.o: $(NETBSD_DIR)/sys/dev/usb/ukbd.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/ums.o: $(NETBSD_DIR)/sys/dev/usb/ums.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/xhci.o: $(NETBSD_DIR)/sys/dev/usb/xhci.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/subr_autoconf.o: $(NETBSD_DIR)/sys/kern/subr_autoconf.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/subr_device.o: $(NETBSD_DIR)/sys/kern/subr_device.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/kern_pmf.o: $(NETBSD_DIR)/sys/kern/kern_pmf.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/hid.o: $(NETBSD_DIR)/sys/dev/hid/hid.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/hidkbdmap.o: $(NETBSD_DIR)/sys/dev/hid/hidkbdmap.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/hidms.o: $(NETBSD_DIR)/sys/dev/hid/hidms.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/dev_verbose.o: $(NETBSD_DIR)/sys/dev/dev_verbose.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/dwc3_fdt.o: $(NETBSD_DIR)/sys/dev/fdt/dwc3_fdt.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/imx8mq_usbphy.o: $(NETBSD_DIR)/sys/arch/arm/nxp/imx8mq_usbphy.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/tpcalib.o: $(NETBSD_DIR)/sys/dev/wscons/tpcalib.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

	
$(BUILD_DIR)/%.o: %.s Makefile
	$(AS) -g3 -mcpu=$(CPU) $< -o $@

$(BUILD_DIR)/mem_handler.elf: $(addprefix $(BUILD_DIR)/, $(MEM_OBJS))
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@

$(BUILD_DIR)/software.elf: $(addprefix $(BUILD_DIR)/, $(SOFTWARE_OBJS))
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@

$(BUILD_DIR)/xhci_stub.elf: $(addprefix $(BUILD_DIR)/, $(XHCI_STUB_OBJS))
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@

$(BUILD_DIR)/hardware.elf: $(addprefix $(BUILD_DIR)/, $(HARDWARE_OBJS))
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@

$(BUILD_DIR)/kbd_logger.elf: $(addprefix $(BUILD_DIR)/, $(KBD_LOGGER_OBJS))
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@

$(BUILD_DIR)/simulated_kbd.elf: $(addprefix $(BUILD_DIR)/, $(SIMULATED_KBD_OBJS))
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@

$(IMAGE_FILE) $(REPORT_FILE): $(addprefix $(BUILD_DIR)/, $(IMAGES)) xhci_stub.system
	$(MICROKIT_TOOL) xhci_stub.system --search-path $(BUILD_DIR) --board $(MICROKIT_BOARD) --config $(MICROKIT_CONFIG) -o $(IMAGE_FILE) -r $(REPORT_FILE)

# clean
clean:
	rm -f *.o *.elf .depend*
	find . -name \*.o |xargs --no-run-if-empty rm
