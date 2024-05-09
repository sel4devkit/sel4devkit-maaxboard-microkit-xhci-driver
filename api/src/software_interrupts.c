/* This work is Crown Copyright NCSC, 2023. */
#include <microkit.h>
#include <pdprint.h>

#include <machine/bus_funcs.h>

#include <dev/usb/xhcivar.h>
#include <dev/usb/umassvar.h>

#include <wrapper.h>
#include <dma.h>
#include <sys/bus.h>
#include <sys/device.h>
#include <sys/device_impl.h>
#include <sys/intr.h>
#include <sys/kernel.h>
#include <sys/kmem.h>

#include <timer.h>
#include <shared_ringbuffer.h>
#include <dev/usb/usb.h>
#include <dev/usb/usb_quirks.h>
#include <dev/usb/usbdi.h>
#include <dev/usb/usbdi_util.h>
#include <dev/usb/usbdivar.h>
#include <dev/usb/usbhist.h>
#include <dev/usb/usb_mem.h>
#include <dev/usb/xhcireg.h>
#include <dev/usb/xhcivar.h>
#include <sys/device.h>
#include <machine/types.h>
#include <sel4_bus_funcs.h>

#include <dev/fdt/fdtvar.h>
#include <config_methods.h>
#include <xhci_api.h>
#include <stdio.h>
#include <stdlib.h>

#define SOFTC_SHARE 1
#define INTR_SHARE 2
#define HOTPLUG 3;

// Setup for getting printf functionality working {{{
static int
libc_microkit_putc(char c, FILE *file)
{
    (void) file; /* Not used by us */
    microkit_dbg_putc(c);
    return c;
}

static int
sample_getc(FILE *file)
{
	return -1; /* getc not implemented, return EOF */
}
static FILE __stdio = FDEV_SETUP_STREAM(libc_microkit_putc,
                    sample_getc,
                    NULL,
                    _FDEV_SETUP_WRITE);
FILE *const stdin = &__stdio; __strong_reference(stdin, stdout); __strong_reference(stdin, stderr);
// END OF LIBC
// }}}

char* pd_name = "software_interrupts";
int num_devices = 0; //unused

uintptr_t xhci_base;
uintptr_t dma_base;
uintptr_t ring_base;
uintptr_t heap_base;
uintptr_t dma_cp_paddr;
uintptr_t timer_base;
uint64_t heap_size = 0x2000000;

//API shared mem
uintptr_t kbd_free;
uintptr_t kbd_used;
uintptr_t mse_free;
uintptr_t mse_used;
uintptr_t uts_free;
uintptr_t uts_used;
uintptr_t umass_resp;
uintptr_t umass_req;
uintptr_t usb_new_device_free; // unused
uintptr_t usb_new_device_used; // unused

// shared memory between client and driver
uintptr_t shared_mem;

bool pipe_thread;

//extern variables
struct xhci_softc *glob_xhci_sc	= NULL;
struct usbd_bus_methods *xhci_bus_methods_ptr;
struct intr_ptrs_holder *intr_ptrs;
int cold = 1;

// shared heap base with client
uintptr_t shared_heap;
uintptr_t shared_soft_heap;

/* Pointers to shared_ringbuffers */
ring_handle_t *kbd_buffer_ring;
ring_handle_t *mse_buffer_ring;
ring_handle_t *uts_buffer_ring;
blk_queue_handle_t *umass_buffer_ring;
ring_handle_t *usb_new_device_ring; // unused

void
init(void) {

    config_init();
    cold = 0;

    pipe_thread = false;
    sel4_dma_init(dma_cp_paddr, dma_base, dma_base + 0x200000);
    initialise_and_start_timer(timer_base);

    kbd_buffer_ring = kmem_alloc(sizeof(*kbd_buffer_ring), 0);
    ring_init(kbd_buffer_ring, (ring_buffer_t *)kbd_free, (ring_buffer_t *)kbd_used, NULL, 0);
    mse_buffer_ring = kmem_alloc(sizeof(*mse_buffer_ring), 0);
    ring_init(mse_buffer_ring, (ring_buffer_t *)mse_free, (ring_buffer_t *)mse_used, NULL, 0);
    uts_buffer_ring = kmem_alloc(sizeof(*uts_buffer_ring), 0);
    ring_init(uts_buffer_ring, (ring_buffer_t *)uts_free, (ring_buffer_t *)uts_used, NULL, 0);
    umass_buffer_ring = kmem_alloc(sizeof(*umass_buffer_ring),0);
    blk_queue_init(umass_buffer_ring, umass_req, umass_resp, false, BLK_REQ_QUEUE_SIZE, BLK_RESP_QUEUE_SIZE);
    print_info("Initialised\n");
}

void
notified(microkit_channel ch) {
    switch (ch) {
        case 7:
            if (glob_xhci_sc != NULL) {
                xhci_softintr(&glob_xhci_sc->sc_bus);
                //microkit_notify(HOTPLUG);
            } else {
                print_fatal("sc not defined");
            }
            break;
        default:
            print_warn("soft interrupt unexpected IRQ %d\n", ch);
    }
}

microkit_msginfo
protected(microkit_channel ch, microkit_msginfo msginfo) {
    switch (ch) {
        case SOFTC_SHARE:
            // share xhci softc for use with interrupts
            glob_xhci_sc = (struct xhci_softc *) microkit_msginfo_get_label(msginfo);
            break;
        case INTR_SHARE:
            // pass interrupt structures so callback can be used without hardcoding
            intr_ptrs = kmem_alloc(sizeof(struct intr_ptrs_holder), 0);
            intr_ptrs->ukbd             = &ukbd_intr;
            intr_ptrs->ums              = &ums_intr;
            intr_ptrs->uts              = &uts_intr;
            intr_ptrs->uhidev           = &uhidev_intr;
            intr_ptrs->uhub             = &uhub_intr;
            intr_ptrs->uhid             = &uhid_intr;
            intr_ptrs->umass_wire_state = get_umass_wire_state();
            intr_ptrs->umass_scsipi_cb  = get_umass_scsipi_cb();
            intr_ptrs->umass_null_cb    = get_umass_null_cb();
            return seL4_MessageInfo_new((uint64_t) intr_ptrs, 1, 0, 0);
        default:
            print_warn("softintr unexpected channel %d\n", ch);
    }
    return seL4_MessageInfo_new(0,0,0,0);
}
