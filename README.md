# XHCI_STUB

## DONE:
- Added maaxboard to the build_sdk.py
- Created a (very average) build system
- Pulled in initial bus reads/writes
- Pulled in all netbsd headers required
- Can perform dwc3 bring up
- "Implemented" printf and malloc
    - malloc receives heap base allocated in `xhci_stub.system`
    - printf receives `sel4cp_debug_putc()`
- Pulled in other C files
- DMA done
    - Incredibly basic algorithm that just has a base pointer for virt and phys addresses and then increments
    - No freeing or reallocation possible yet
- Interrupts enabled
    - Hard and soft
- Keyboard driver now included
    - Is able to set up keyboard to trigger hardware interrupts
    - LEDs not quite working yet (can probably sort this later)
    - Includes (incredibly) basic prototype: will output basic characters, no use of shift or ctrl (but the presses are actually registered).

## TODO:
- Neaten up code sooner rather than later
    - Look at CMake now
    - Platform headers for future proofing
    - Headers for things like heap size and heap base
- Setup condition variables
- Send keypresses to PD

## Bugs/strange things/important changelog
- `xhci_setup_route` should include path of root hub, but doesn't. No issues because of this yet, but something to look at in the future if breakages happen
- `xfer->ux_callback()` commented out and replaced with `uhub_intr()` or `device_ctrl_intr()`. Will likely become a problem in the future, but right now it works.
    - A few other hard commented quirks, such as `uhidev_attach` and `ukbd_intr`
- Setting MaxBrate of device in `xhci_new_device` returns 0, overwriting correct value returned by `get_initial_ddesc()` if device speed is not ss. Fixed by checking if 0 is returned and if so using the ddesc value.
- `bus_methods` replaced with pointer to `xhci_bus_methods` because this is an xhci driver, so assume that it's always going to use an xhci bus.
- `cv_waitsig()` replaced with `usbd_delay_ms(0, 100)` to delay 100ms instead of waiting for cv to change.
- `xfer->ux_status` set to `USBD_IN_PROGRESS` before doing anything else (different to netbsd which schedules a callout).
- Callouts not set, meaning timeout will never happen (netbsd waits 5s)

## External sources
- Tiny alloc: https://github.com/thi-ng/tinyalloc/tree/master
    - License: apache
- printf: https://github.com/mpaland/printf/tree/master
    - License: MIT
- memset/memcpy/strlen etc etc: pulled from linux source, stored in util.c
    - License: whatever linux has (I think BSD)