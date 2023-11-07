/* This work is Crown Copyright NCSC, 2023. */
#include <microkit.h>
#include <printf.h>

#include <machine/bus_funcs.h>

#include <dev/usb/xhcivar.h>

#include <wrapper.h>
#include <tinyalloc.h>
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
#include <dev/usb/usbdi.h>
#include <dev/usb/usbdivar.h>
#include <dev/usb/usbhist.h>
#include <dev/usb/usb_mem.h>
#include <dev/usb/xhcireg.h>
#include <dev/usb/xhcivar.h>
#include <sys/device.h>
#include <machine/types.h>
#include <sel4_bus_funcs.h>
#include <libfdt.h>

#include <lib/libkern/libkern.h>
#include <dev/fdt/fdtvar.h>
#define BUS_DEBUG 0
#define __AARCH64__

//extern variables
bool int_once = false;
struct xhci_softc *glob_xhci_sc	= NULL;
struct usb_softc *glob_usb_sc 	= NULL;
struct usbd_bus_methods *xhci_bus_methods_ptr;
uintptr_t xhci_root_intr_pointer;
uintptr_t xhci_root_intr_pointer_other;
uintptr_t device_ctrl_pointer;
uintptr_t device_ctrl_pointer_other;
uintptr_t device_intr_pointer;
uintptr_t device_intr_pointer_other;
uintptr_t rx_free;
uintptr_t rx_used;
uintptr_t tx_free;
uintptr_t tx_used;

struct intr_ptrs_holder *intr_ptrs;
bool pipe_thread;
int cold = 1;

struct imx8mq_usbphy_softc {
	device_t		sc_dev;
	bus_space_tag_t		sc_bst;
	bus_space_handle_t	sc_bsh;
	int			sc_phandle;
};

// definitions from .system file
uintptr_t xhci_base;
uintptr_t xhci_phy_base;
uintptr_t heap_base;
uint64_t heap_size = 0x2000000;
int ta_blocks = 256;
int ta_thresh = 16;
int ta_align = 64;
uintptr_t pipe_heap_base;
uintptr_t dma_base;
uintptr_t dma_cp_paddr;
uintptr_t dma_cp_vaddr = 0x54000000;
uintptr_t ta_limit;
uintptr_t timer_base;
uintptr_t software_heap;

struct usb_softc *usb_sc, *usb_sc2;

/* Pointers to shared_ringbuffers */
ring_handle_t *kbd_buffer_ring;

void
init(void) {
    //initialise autoconf data structures
    config_init(); 

    pipe_thread = false;
    cold = 0;

    // initialise structures. Communicate with software interrupt pd to get back all required data structures
    xhci_bus_methods_ptr            = (struct usbd_bus_methods *) get_bus_methods();
    intr_ptrs                       = (struct intr_ptrs_holder *) microkit_msginfo_get_label(microkit_ppcall(8, seL4_MessageInfo_new(0,0,0,0)));
    xhci_root_intr_pointer          = (uintptr_t) get_root_intr_methods();
    device_ctrl_pointer             = (uintptr_t) get_device_methods();
    device_intr_pointer             = (uintptr_t) get_device_intr_methods();
    xhci_root_intr_pointer_other    = (uintptr_t) microkit_msginfo_get_label(microkit_ppcall(1, seL4_MessageInfo_new((uint64_t) xhci_root_intr_pointer,1,0,0)));
    device_ctrl_pointer_other       = (uintptr_t) microkit_msginfo_get_label(microkit_ppcall(3, seL4_MessageInfo_new((uint64_t) device_ctrl_pointer,1,0,0)));
    device_intr_pointer_other       = (uintptr_t) microkit_msginfo_get_label(microkit_ppcall(4, seL4_MessageInfo_new((uint64_t) device_intr_pointer,1,0,0)));
    uintptr_t fdt = microkit_msginfo_get_label(microkit_ppcall(44, seL4_MessageInfo_new(0,0,0,0)));
    printf("fdt magic = 0x%x\n", fdt_magic(fdt));

    fdtbus_init(fdt);

	int offset = -1;

    offset = fdt_next_node(fdt, offset, NULL);
    int dwc3_phandle = fdtbus_offset2phandle(offset);
    bus_size_t addr, size;
    printf("Traversing FDT to find dwc3 node at 0x%x...\n", xhci_base);
    while (addr != xhci_base) {
        offset = fdt_next_node(fdt, offset, NULL);
        if (offset < 0) {
            if (offset == -FDT_ERR_NOTFOUND) {
                printf("FATAL ERROR: no dwc3 node at 0x%x. Exiting.\n", xhci_base);
                return;
            }
        }
        dwc3_phandle = fdtbus_offset2phandle(offset);
        fdtbus_get_reg(dwc3_phandle, 0, &addr, &size);
    }
    printf("XHCI_STUB: dwc3_phandle = %x\n", dwc3_phandle);
    printf("addr = 0x%x, size = 0x%x\n", addr, size);

    // offset = -1;
    initialise_and_start_timer(timer_base);

    sel4_dma_init(dma_cp_paddr, dma_cp_vaddr, dma_cp_vaddr + 0x200000);

    // setup xhci devices + tell software PD memory locations
    device_t parent_xhci = NULL;
    kbd_buffer_ring = kmem_alloc(sizeof(*kbd_buffer_ring), 0);

    device_t self_xhci = kmem_alloc(sizeof(device_t), 0);
    struct fdt_attach_args *aux_xhci = kmem_alloc(sizeof(struct fdt_attach_args), 0);

    aux_xhci->faa_phandle = dwc3_phandle;

    struct xhci_softc *sc_xhci = kmem_alloc(sizeof(struct xhci_softc), 0);
    glob_xhci_sc = sc_xhci;
    sc_xhci->sc_ioh=xhci_base;
    microkit_ppcall(0, seL4_MessageInfo_new((uint64_t) sc_xhci,1,0,0));
    microkit_ppcall(2, seL4_MessageInfo_new((uint64_t) sc_xhci,1,0,0));
	bus_space_tag_t iot = kmem_alloc(sizeof(bus_space_tag_t), 0);
    sc_xhci->sc_iot=iot;

    self_xhci->dv_private = sc_xhci;

    dwc3_fdt_attach(parent_xhci,self_xhci,aux_xhci);
    // attach USB3 bus
    usb_sc              = kmem_alloc(sizeof(struct usb_softc),0);
    device_t self       = kmem_alloc(sizeof(device_t), 0);
    self->dv_unit       = 1;
    self->dv_private    = usb_sc;
    usb_sc->sc_bus      = &glob_xhci_sc->sc_bus;
    usb_attach(self_xhci, self, &glob_xhci_sc->sc_bus);

    // attach USB2 bus
    struct usbd_bus *sc_bus2;
    usb_sc2               = kmem_alloc(sizeof(struct usb_softc),0);
    sc_bus2               = kmem_alloc(sizeof(struct usbd_bus),0)
    device_t self2        = kmem_alloc(sizeof(device_t), 0);
    *sc_bus2              = glob_xhci_sc->sc_bus2;
    sc_bus2->ub_methods   = glob_xhci_sc->sc_bus2.ub_methods;
    self2->dv_private     = usb_sc2;
    self2->dv_unit        = 1;
    usb_sc2->sc_bus       = sc_bus2;
    usb_attach(self_xhci, self2, sc_bus2);

    // assert initial explore
	usb_sc->sc_bus->ub_needsexplore    = 1;
	usb_sc2->sc_bus->ub_needsexplore   = 1;

    // setup complete, busses will still need to be explored for devices to function
    printf("\nxHCI driver ready\n");
}



void
notified(microkit_channel ch)
{
    switch (ch) {
        case 17: // hotplug
            // do a discover
            if (usb_sc->sc_bus->ub_needsexplore) {
                printf("Discover on USB3...\n");
                usb_discover(usb_sc);
                printf("USB3 discover finished\n");
            }
            if (usb_sc2->sc_bus->ub_needsexplore) {
                printf("Discover on USB2...\n");
                usb_discover(usb_sc2);
                printf("USB2 discover finished\n");
            }
            break;
        default:
            printf("xhci_stub received notification unexpected channel\n");
    }
}

microkit_msginfo
protected(microkit_channel ch, microkit_msginfo msginfo) {
    switch (ch) {
        case 1:
            // return addr of root_intr_methods
            xhci_root_intr_pointer = (uintptr_t) microkit_msginfo_get_label(msginfo);
            break;
        default:
            printf("xhci_stub received protected unexpected channel\n");
    }
    return seL4_MessageInfo_new(0,0,0,0);
}
