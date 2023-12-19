#include <xhci_api.h>
#include <stddef.h>
#include <stdbool.h>
#include <shared_ringbuffer.h>
#include <printf.h>
#include <stdlib.h>
#include <math.h>

// TEMP
#define kmem_zalloc(size, km_flag_t) (void*) microkit_msginfo_get_label(microkit_ppcall(31, seL4_MessageInfo_new(size, 1, 0, 0)));
#define kmem_alloc(size, km_flag_t) (void*) microkit_msginfo_get_label(microkit_ppcall(30, seL4_MessageInfo_new(size, 1, 0, 0)));
#define kmem_free(addr, size_t) microkit_msginfo_get_label(microkit_ppcall(32, seL4_MessageInfo_new((uintptr_t)addr, 1, 0, 0)));

uintptr_t umass_free;
uintptr_t umass_used;
ring_handle_t *api_request_ring;
extern ring_handle_t *umass_buffer_ring;

// buffers for devices
extern uintptr_t kbd_free;
extern uintptr_t kbd_used;
extern uintptr_t mse_free;
extern uintptr_t mse_used;
extern uintptr_t uts_free;
extern uintptr_t uts_used;
extern uintptr_t umass_req_free;
extern uintptr_t umass_req_used;

static int current_xfer = -1;
static bool locked = false;
struct umass_request *active_xfer;

ring_handle_t *usb_new_device_ring;
uintptr_t usb_new_device_free;
uintptr_t usb_new_device_used;

int umass_id = 0;
int num_devices = 0;
struct sel4_usb_device* usb_devices[MAX_DEVICES];

int execute_next();

/**
 * api_init(): initialise structures required by api
*/
void api_init(ring_handle_t **kbd, ring_handle_t **mse, ring_handle_t **uts, ring_handle_t **umass) {
    *kbd = (ring_handle_t*) malloc(sizeof(ring_handle_t));
    ring_init(*kbd, (ring_buffer_t *)kbd_free, (ring_buffer_t *)kbd_used, NULL, 0);
    *mse = (ring_handle_t*) malloc(sizeof(ring_handle_t));
    ring_init(*mse, (ring_buffer_t *)mse_free, (ring_buffer_t *)mse_used, NULL, 0);
    *uts = (ring_handle_t*) malloc(sizeof(ring_handle_t));
    ring_init(*uts, (ring_buffer_t *)uts_free, (ring_buffer_t *)uts_used, NULL, 0);
    *umass = (ring_handle_t*) malloc(sizeof(ring_handle_t));
    ring_init(*umass, (ring_buffer_t *)umass_req_free, (ring_buffer_t *)umass_req_used, NULL, 0);

    // umass specific initialisation
    api_request_ring = kmem_alloc(sizeof(ring_buffer_t), 0);
    umass_free = (uintptr_t) kmem_alloc(0x200000, 0);
    umass_used = (uintptr_t) kmem_alloc(0x200000, 0);
    ring_init(api_request_ring, (ring_buffer_t *)umass_free, (ring_buffer_t *)umass_used, NULL, 1);

    // New deivce event ring
    usb_new_device_ring = kmem_alloc(sizeof(*usb_new_device_ring), 0);
    ring_init(usb_new_device_ring, (ring_buffer_t *)usb_new_device_free, (ring_buffer_t *)usb_new_device_used, NULL, 0);
}

int enqueue_umass_request(int dev_id, bool read, int blkno, int nblks, void* val, void* cb) {
    int xfer_id = ++current_xfer;
    struct sel4_usb_device *dev = usb_devices[dev_id];
    if (!(dev->class == 0 && dev->ifaceClass == 0x8)) {
        printf("Device is not a mass storage device\n");
        return -1;
    }

    struct umass_request* umass_xfer = kmem_alloc(sizeof(struct umass_request), 0);

    umass_xfer->dev_id = dev->id;
    umass_xfer->umass_id = dev->umass_dev->umass_id;
    umass_xfer->read = read;
    umass_xfer->blkno = blkno;
    umass_xfer->nblks = nblks;
    umass_xfer->val = val;
    umass_xfer->cb = cb;
    umass_xfer->xfer_id = xfer_id;

    enqueue_used(dev->umass_dev->api_request_ring, (uintptr_t) umass_xfer, sizeof(umass_xfer), (void*)0);

    // ensure reads and writes are executed in the order they arrived
    if (!dev->umass_dev->locked) {
        dev->umass_dev->locked = true;
        return execute_next(dev);
    } else {
        printf("device busy\n");
    }

    return xfer_id;
}

int execute_next(struct sel4_usb_device* dev) {
    uintptr_t *buffer = 0;
    unsigned int len = 0;
    void *cookie = NULL;

    int index;
    if (!driver_dequeue(dev->umass_dev->api_request_ring->used_ring, (uintptr_t*)&buffer, &len, &cookie)) {
        struct umass_request* xfer = (struct umass_request*)buffer; 
        printf("xfer_id: %i    blkno: %i    nblks: %i\n", xfer->xfer_id, xfer->blkno, xfer->nblks);
        dev->umass_dev->active_xfer = xfer;

        bool empty = ring_empty(umass_buffer_ring->used_ring);
        int error = enqueue_used(umass_buffer_ring, (uintptr_t) xfer, sizeof(xfer), (void *)0);
        if (empty)
            microkit_notify(47);

        return xfer->xfer_id;
    } else {
        return -1;    
    }
}

/**
 * Handle completed umass request. Does callback, and enqueues next request if there is one
*/
void handle_xfer_complete()
{
    uintptr_t *buffer = 0;
    unsigned int len = 0;
    void *cookie = NULL;
    if(!driver_dequeue(umass_buffer_ring->free_ring, (uintptr_t*)&buffer, &len, &cookie)) {
        printf("dequeue %d\n", (int)*buffer);
        struct sel4_usb_device* dev = usb_devices[(int)*buffer];
        // do callback
        if (dev->umass_dev->active_xfer->cb)
            (dev->umass_dev->active_xfer->cb)(dev->umass_dev->active_xfer);

        dev->umass_dev->active_xfer = NULL;
        dev->umass_dev->locked = false;
        kmem_free(buffer,0);

        // if ring is not empty, do next xfer
        if (!ring_empty(dev->umass_dev->api_request_ring)) {
            execute_next(dev);
        }
    }
}

void setup_mass_storage(struct sel4_usb_device* dev) {
    struct sel4_umass_device* new_umass_dev = kmem_alloc(sizeof(struct sel4_umass_device), 0);

    new_umass_dev->api_request_ring = kmem_alloc(sizeof(ring_buffer_t), 0);
    ring_buffer_t *free_ring = (ring_buffer_t*) kmem_zalloc(0x200000, 0);
    ring_buffer_t *used_ring = (ring_buffer_t*) kmem_zalloc(0x200000, 0);
    ring_init(new_umass_dev->api_request_ring, free_ring, free_ring, NULL, 1);

    new_umass_dev->umass_id = umass_id++;
    new_umass_dev->locked = false;
    new_umass_dev->active_xfer = NULL;

    dev->umass_dev = new_umass_dev;
}

void
handle_new_device() {
    uintptr_t *buffer = 0;
    unsigned int len = 0;
    void *cookie = NULL;

    int index;
    while (!driver_dequeue(usb_new_device_ring->used_ring, (uintptr_t*)&buffer, &len, &cookie)) {
        struct sel4_usb_device* dev = (struct sel4_usb_device*)buffer; 
        num_devices = num_devices > dev->id ? num_devices : dev->id;
        usb_devices[dev->id] = dev; 
        if (dev->class == 0)
            if (dev->ifaceClass == 0x8)
                setup_mass_storage(dev);
    }
}

char* get_class(int class) {
    switch(class) {
        case 0: 
            return "Device";
        case 1: 
            return "audio";
        case 2: 
            return "CDC";
        case 3: 
            return "HID";
        case 5: 
            return "Physical";
        case 6: 
            return "Image";
        case 7: 
            return "Printer";
        case 8: 
            return "Mass storage";
        case 9: 
            return "Hub";
        default:
            return "None";
    }
}

char* get_speed(int speed) {
    switch(speed) {
        case USB_SPEED_LOW: 
            return "LOW";
        case USB_SPEED_FULL: 
            return "FULL";
        case USB_SPEED_HIGH: 
            return "HIGH";
        case USB_SPEED_SUPER: 
            return "SUPER";
        case USB_SPEED_SUPER_PLUS: 
            return "SUPER PLUS";
        default:
            return "ERROR";
    }
}

void print_device(int id)
{
    struct sel4_usb_device *dev = usb_devices[id];
    if (dev->class == 0)
        printf("%i: %s,\tUSB Revision %02x\n", dev->id, get_class(dev->class), dev->rev);
    else
        printf("%i: %s,\tUSB Revision %02x\n", dev->id, get_class(dev->ifaceClass), dev->rev);
    printf(" - %s %s\n", dev->vendor, dev->product);
    printf(" - Vendor: 0x%04x Product: 0x%04x\n", dev->vendorid, dev->productid);
    printf(" - PacketSize: %d Configurations: %d\n", (int) pow(2, dev->mps), dev->num_configs);
    if (dev->class == 0)
        printf(" - Class: (from interface) %s\n", get_class(dev->class));
    else
        printf(" - Class: %s\n", get_class(dev->class));
    printf(" - Speed: %s\n", get_speed(dev->speed));
    if (dev->class == 0) {
        printf(" - Interface info\n");
        printf("    - Class: %s\n", get_class(dev->ifaceClass));
    }
    printf(" - Depth: %d\n", dev->depth);
}

void print_devs()
{
    for (int i = 0; i <= num_devices; i++) {
        print_device(i);
        printf("\n");
    }
}
