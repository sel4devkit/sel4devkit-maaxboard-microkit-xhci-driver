# seL4 USB 3.0 (xHCI) driver

This repo contains the code for the xHCI driver developed by Capgemini.
The project should be built with this [Docker environment](https://github.com/sel4devkit/sel4devkit-maaxboard-microkit-docker-dev-env).

Specifically, we have provided support for these USB devices:
- Keyboard
- Mouse
- Resistive Touch Screen (Capacitative untested but believed to also be supported)
- USB Hub
- Mass Storage Devices

## Directory structure
- `api/`: Contains the bulk of the files required by the driver to function.
    - `include/`: Headers for api, include for api functions.
    - `src/`: Handles initialisation and handling of interrupts for xHCI driver.
    - `utils`: Auxilliary files for use by the driver.
- `examples`: contain example applications utilising the xHCI driver to demonstrate usage
- `kernel`: contains dtb for desired build (currently ONLY supports maaxboard)
-  `dep/`: Contains the dependencies for the project.
    - `compiler/`: Contains a build script to add download the compiler, extract it and set it to $PATH.
    - `microkit/` : Contains instructions to clone a prebuilt version of the SDK.
    - `netbsd/`: Capgemini fork of NetBSD customised to function in the context of microkit.
    - `picolibc` : Contains instructions to clone a picolibc repository and copy the necessary files.
- `build.sh`: shell file to set up required environment variables and call makefile. Can be used with the following options:
    - Specify example with `-e`. Examples:
        - empty-client: Simple client that prints out list of connected (and supported) devices.
        - shell: More advanced example shell, demonstrates exensive use of driver and API.
    - Build flags:
        - `-c` clean: remove all object files
        - `-r` rebuild: remove all object files and build from scratch,
        - `-d` debug: enable extensive xhci debug print statements (as per standard netbsd logging output)
            - TODO: add logging levels to fine tune output    
- `Makefile`: to be used via `build.sh`. Builds system.

## Requirements
- This driver expects to have the accompanying NetBSD fork.
  - Use branch 'trunk' for netbsd.  Located [here](https://github.com/sel4devkit/sel4devkit-maaxboard-microkit-netbsd-fork).
- This driver assumes the existence of a built Microkit SDK. Located [here](https://github.com/sel4devkit/sel4devkit-maaxboard-microkit-dev).
- This driver assumes a pre-built microkit libc. Located [here](https://github.com/sel4devkit/sel4devkit-maaxboard-microkit-picolibc).
    - Use branch linker_crt
    - See below for build and use instructions

## Building
### Building the dependencies

```
cd dep
make get
```
To remove dependencies
```
make clean
```
The dependencies can be built individually by navigating to the appopriate folder apart from the compiler and SDDF which don't have their own Makefile. Note: **SDDF is located in the api/sDDF directory.**

### Build example
To build this driver, use the `build.sh` bash script.

Breakdown of variables set:
- `MICROKIT_SDK`: Repository of microkit SDK
- `MICROKIT_BOARD`: Board to create image for (default: maaxboard)
- `MICROKIT_CONFIG`: Configuration to build with (default: debug)
- `MICROKIT_TOOL`: Path to microkit tool
- `BOARD_DIR`: Directory used by Microkit to pull includes
- `BUILD_DIR`: (Can be modified) directory to produce image file
- `PYTHONPATH`: Used by python microkit tool
- `SEL4_XHCI_PATH`: Path of xhci_stub/ directory
- `NETBSD_DIR`: Path of netbsd directory

By default, the driver will build with an empty example client that is subscribed to all interrupt channels. Data will not be handled. Upon successful initialisation, a list of devices plugged into the board will be printed.

The driver can be built with either a shell example (provides a shell like program), or an empty client that is subscribed to all channels, and will print a list of supported devices plugged into the board. The usage is as follows:

```sh
./build.sh -e shell # or empty-client, FatFs
```
Note: **The option -c must be used to clean the directory when switching between examples.**

Call `./build.sh` with no arguments to see optional flags.

## Setup
The driver will require some memory regions to be mapped into both the driver PD and the client PD. Here is a list of the required memory regions:
- **Free/used buffers** for each communication ring. Suggested size of each of these is around `0x200_000`, but any size can be used. Each of these should be mapped into xhci_stub, software_interrupt, and client PD.
    - `kbd_free/kbd_used`
    - `umass_resp/umass_req`
    - `mse_free/mse_used`
    - `uts_free/uts_used`
    - `usb_new_device_free/usb_new_device_used`
- **Shared heaps** to store data structures that would need to be shared between the PDs. These are already mapped into the pre-existing PDs, but should be also mapped into the client PD. They need to have a consistent address space to ensure continuity between PDs. The size for these heaps is `0x200_000`, and the memory region names and associated virtual addresses are:
    - `shared_heap`: `vaddr=0x5_a00_000`
    - `shared_soft_heap`: `vaddr=0x5_800_000`
- **libc heap**: a heap start and end to be used by picolibc. They must be mapped to `__heap_start` and `__heap_end` in the client PD.
    - Note: for the time being, two distinct memory regions are required, with `__heap_end` simulating the end of the heap, and size should be as small as possible (`0x1000`).

Examples of these can be seen in the `xhci_stub.system` file.

## Using driver
To use the driver, see the sample client (in `empty-client`). The example is already *subscribed* to all 4 devices.

To subscribe to an interrupt, modify the `.system` file to connect the client to the appropriate channel (see below) and include in the `notified()` function in the client PD..

### Init (channel: 40)
This is a software interrupt generated by the driver to notify initial setup is complete. Note, if a USB hub is connected, further setup may occur for a short while afterwards.

Example:
```xml
<!-- Driver initialise complete -->
<channel>
    <end pd="xhci_stub" id="40"/><!--must be mapped to xhci_stub-->
    <end pd="example_pd" id="40"/>
</channel>
```

### New device (channel: 45)
Interrupt generated on new device connection. To allow the API to handle this new device, use `handle_new_device()`. The API will decode the information sent by the driver and populate a list of devices (`device_list`) as they are connected. This list can be accessed, and each entry is of type `struct sel4_usb_device`. This structure is as follows:

- id: device id
- vendor: vendor string
- product: product string
- vendorid: vendor hex code
- productid: product hex code
- class: class of device (if 0, check interface)
- subclass: subclass of device
- ifaceClass: interface class
- ifaceSub: interface sub class
- depth: how many connections from host controller device is
- speed: speed of device
- protocol: USB protocol
- mps: max packet size (CURRENTLY BROKEN)
- len: length of packet
- num_configs: number of configs
- rev: USB revision
- umass_dev: mass storage specific information
    - umass_id: mass storage specific id
    - locked: mutex to ensure only one process can occur at a given time
- (sddf mass storage spec)
    - serial_number
    - read_only
    - ready
    - blocksize
    - queue_depth
    - cylinders
    - heads
    - blocks
    - size

The hex codes for vendor and product can be used to look up device specific information in the USB-IF database.

```xml
<!-- USB Device Connect Event -->
<channel>
    <end pd="xhci_stub" id="45"/> <!-- must be mapped to xhci_stub -->
    <end pd="example_pd" id="45"/>
</channel>
```

### Keyboard (channel: 46)
The keyboard interrupt signifies a key event generated from the keyboard. The driver will create a buffer in the `kbd_buffer_ring->used_ring` that can be dequeued and processed as desired. To dequeue a buffer, use `dequeue_free(kbd_buffer_ring, buffer, len, NULL)` where the data is written `buffer` which is a pointer of length `len`.

The buffer is an array of hexadecimal codes where the first 2 entries are reserved for special codes, and the others (length depends on keyboard) give the state of the keyboard (keys currently pressed). Note that this channel will fire on both key down and key up events, so it may be useful to store the previous buffer state to calculate which key is unique. If too many keypresses are input for a specific keyboard, all entries in this buffer will be set to `0x1`.

The first item in the buffer (`buffer[0]`) corresponds to:
- `0x01`: Ctrl
- `0x02`: Shft
- `0x04`: Alt
- ...

To get the keycode of a buffer entry, use `buffer[id]&0xFF`. This keycode can then be used as a key to a keyboard decoding table. An example table is included in `wsksymdef.h`.

Example:
```xml
<!-- Keyboard interrupt -->
<channel>
    <end pd="software_interrupt" id="45"/> <!-- must be mapped to software interrupt -->
    <end pd="example_pd" id="45"/>
</channel>
```

### Mouse (channel: 48)
The mouse interrupt is generated on mouse move or click. Similar to keyboard, the driver will create a buffer in `mse_buffer_ring->used_ring`, and can be dequeued by the client progam using `dequeue_free` as before.

The buffer is an array of changes to the direction of the mouse, and can be used as follows:
- `buffer[0]`: x direction
- `buffer[1]`: y direction
- `buffer[2]`: wheel direction
- `buffer[3]`: z direction
- `buffer[4]`: Mouse buttons, a flag indicating buttons down:
    - `0x1`: left
    - `0x2`: middle
    - `0x4`: right

### Touchscreen (channel: 49)
The touchscreen interrupt is generated on a touch event. Similar to mouse, the driver will create a buffer in `uts_buffer_ring->used_ring`, and can be dequeued by the client program using `dequeue_free` as before.

The buffer contains the x and y coordinates, and a z value, which indicates pressure (supported by some hardware). It also has buttons held.
- `buffer[0]`: x coordinate
- `buffer[1]`: y coordinate
- `buffer[2]`: z value
- `buffer[3]`: Buttons, a flag indicating buttons down:
    - `0x1`: left
    - `0x2`: middle
    - `0x4`: right
### Mass storage (channel: 50)
Mass storage works in a different way to the previously mentioned devices, since this device will not generate interrupts without software interaction. This API allows a read/write command to be passed to the driver, which will return with the desired output.

For both commands, `enqueue_umass_request()` is used. The API handles the locking and unlocking of devices and keeps track of the transfer requests automatically. The arguments to this command are as follows:
- `int dev_id`: ID of device to send request to. Must be a mass storage device.
- `bool read`: True for read request, false for write request
- `int blkno`: Block number in device to start operation
- `int nblks`: Number of blocks to perform operation on (NOTE: currently limited to 8)
- `void* val`: Used differently depending on read/write
    - Read: Pointer in shared data to write data
    - Write: Pointer in shared data containing value to write
- `void* cb`: Optional callback function that is called on transfer completion.

The shell example also permits filesystem reads/writes/lists (FAT is the only supported filesystem currently). Note that the mass storage queue is different to that outlined by sDDF. This is due to the `current_xfer` field, that allows the locking and unlocking of client threads when waiting for block access, since reading and writing are both *synchronous* in the current version.

## CHANGELOG
### DONE:
- Added maaxboard to the build_sdk.py
- Created a build system
- Pulled in initial bus reads/writes
- Pulled in all netbsd headers required
- Can perform dwc3 bring up
- Implemented full c standard library (picolibc)
    - malloc receives heap base allocated in `xhci_stub.system`
    - printf receives `microkit_debug_putc()`
- Pulled in other C files
- DMA done
    - Incredibly basic algorithm that just has a base pointer for virt and phys addresses and then increments
    - No freeing or reallocation possible yet
- Interrupts enabled
    - Hard and soft
- Keyboard driver now included
    - Is able to set up keyboard to trigger hardware interrupts
    - LEDs not quite working yet (can probably sort this later)
        - TODO: They did work briefly, but now don't again
    - Includes basic prototype: will output basic characters, no use of shift or ctrl (but the presses are registered).
- Can send keypresses to separate PD using notifications and shared memory address
    - Other PD handles shift but not altgr
- Mouse driver now included
    - Buttons and direction
- Touch screen driver now included
    - Our device has no z input but should work for those devices that do
- Autoconf to enable switching between devices (attempts to match and attaches to best match) - as opposed to harcoding for specific devices
- USB Hub support now included
    - Tested with 4 devices, more likely to be supported but untested
- Mass storage support
- API created with sample clients
- Synchronous file system added

### TODO:
- Condition variables (?)
- More devices:
    - ~~Mass storage~~ DONE
    - ~~Touchscreen~~ DONE
    - ~~Root hub that isn't the pseudo device~~ DONE
- Simultaneous devices. Work but needs more extensive testing to make sure we don't have any race conditions
- Add sDDF async filesystem

### Bugs/strange things/important changelog
- ~~`xhci_setup_route` should include path of root hub, but doesn't. No issues because of this yet, but something to look at in the future if breakages happen~~
    - **NEW!** Fixed by correctly attaching to roothub and setting up parents properly.
- ~~`xfer->ux_callback()` commented out and replaced with `uhub_intr()` or `device_ctrl_intr()`. Will likely become a problem in the future, but right now it works.~~
    - ~~A few other hard commented quirks, such as `uhidev_attach` and `ukbd_intr`~~
    - **NEW!** No longer a problem. Autoconf introduced to remove attach hardcodings and new structure in usb.h: `intr_ptrs` included to contain pointers to interrupt function in software interrupt PD.
- ~~Setting MaxBRate of device in `xhci_new_device` returns 0, overwriting correct value returned by `get_initial_ddesc()` if device speed is not ss. Fixed by checking if 0 is returned and if so using the ddesc value.~~
    - ~~**NEW!**: fixed by setting up device description memory regions properly.
- `bus_methods` replaced with pointer to `xhci_bus_methods` because this is an xhci driver, so assume that it's always going to use an xhci bus.
- `cv_waitsig()` replaced with `usbd_delay_ms(0, 100)` to delay 100ms instead of waiting for cv to change.
- `xfer->ux_status` set to `USBD_IN_PROGRESS` before doing anything else (different to netbsd which schedules a callout).
- Callouts not set, meaning timeout will never happen (netbsd waits 5s)
- Autoconf pulled in manually.
    - Makes use of ioconf.c which is generated on build of netbsd - hardware (board) specific to a degree
    - Devices are uncommented as and when needed to reduce searching overhead
- ~~Hot plugging not implemented (requires a task thread that would have to be a separate PD)~~
    - **NEW!**: Hot plugging implemented (does not work with external hubs), separate PD not necessary.
- ~~RepID issue with touch screen - so prevented from becoming 0 (and crashing)~~
    - **NEW!** fixed. Slight bug in setting parent structure fixed.

### Currently supported autoconf devices

| **Device** | **Name in ioconf.c** | **Notes** |
| --- | --- | --- |
| USB | usb | General usb functions |
| Roothub | uroothub | Enables root hub capabilities |
| USB Hub | uhub    | Physical USB Hub |
| Human interface device | uhidev | General parent for any HIDs (keyboard, mouse, etc) |
| Keyboard | ukbd | Keyboard driver |
| Mouse    | ums  | Mouse driver |
| Touchscreen | uts | Touch screen driver |
| Mass storage | umass | Mass storage |
