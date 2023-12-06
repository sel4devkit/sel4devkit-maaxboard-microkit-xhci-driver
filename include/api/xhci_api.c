#include <xhci_api.h>
#include <stddef.h>
#include <stdbool.h>
#include <shared_ringbuffer.h>
#include <sys/kmem.h>
#include <printf.h>

uintptr_t umass_free;
uintptr_t umass_used;
ring_handle_t *api_request_ring;
extern ring_handle_t *umass_buffer_ring;

static int current_xfer = -1;
static bool locked = false;
struct umass_request *active_xfer;

ring_handle_t *usb_new_device_ring;
uintptr_t usb_new_device_free;
uintptr_t usb_new_device_used;

int dev_id;
struct usb_new_device* usb_devices[MAX_DEVICES];

int execute_next();

/**
 * umass_api_init(): initialise rings required by api
*/
void umass_api_init() {
    api_request_ring = kmem_alloc(sizeof(ring_buffer_t), 0);
    umass_free = (uintptr_t) kmem_alloc(0x200000, 0);
    umass_used = (uintptr_t) kmem_alloc(0x200000, 0);
    ring_init(api_request_ring, (ring_buffer_t *)umass_free, (ring_buffer_t *)umass_used, NULL, 1);
    // New deivce event ring
    usb_new_device_ring = kmem_alloc(sizeof(*usb_new_device_ring), 0);
    ring_init(usb_new_device_ring, (ring_buffer_t *)usb_new_device_free, (ring_buffer_t *)usb_new_device_used, NULL, 0);
    dev_id = 0;
}


int enqueue_umass_request(int dev_id, bool read, int blkno, int nblks, void* val, void* cb) {
    int xfer_id = ++current_xfer;

    struct umass_request* umass_xfer = kmem_alloc(sizeof(struct umass_request), 0);

    umass_xfer->dev_id = dev_id;
    umass_xfer->read = read;
    umass_xfer->blkno = blkno;
    umass_xfer->nblks = nblks;
    umass_xfer->val = val;
    umass_xfer->cb = cb;
    umass_xfer->xfer_id = xfer_id;

    enqueue_used(api_request_ring, (uintptr_t) umass_xfer, sizeof(umass_xfer), (void*)0);

    // ensure reads and writes are executed in the order they arrived
    if (!locked) {
        locked = true;
        return execute_next();
    } else {
        printf("device busy\n");
    }

    return xfer_id;
}

int execute_next() {
    uintptr_t *buffer = 0;
    unsigned int len = 0;
    void *cookie = NULL;

    int index;
    if (!driver_dequeue(api_request_ring->used_ring, (uintptr_t*)&buffer, &len, &cookie)) {
        struct umass_request* xfer = (struct umass_request*)buffer; 
        printf("xfer_id: %i    blkno: %i    nblks: %i\n", xfer->xfer_id, xfer->blkno, xfer->nblks);
        active_xfer = xfer;

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
    // do callback
    if (active_xfer->cb)
        (active_xfer->cb)(active_xfer);

    active_xfer = NULL;
    locked = false;

    // if ring is not empty, do next xfer
    if (!ring_empty(api_request_ring)) {
        execute_next();
    }
}

void
handle_new_device() {
    uintptr_t *buffer = 0;
    unsigned int len = 0;
    void *cookie = NULL;

    int index;
    while (!driver_dequeue(usb_new_device_ring->used_ring, (uintptr_t*)&buffer, &len, &cookie)) {
        struct usb_new_device* dev = (struct usb_new_device*)buffer; 
        dev->id = dev_id++;
        usb_devices[dev->id] = dev; 
        //print_device(dev->id);
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
    struct usb_new_device *dev = usb_devices[id];
    printf("USB device:\n");
    printf("    ID: %i\n", dev->id);
    printf("    Vendor: %s (0x%04x)\n", dev->vendor, dev->vendorid);
    printf("    Product: %s (0x%04x)\n", dev->product, dev->productid);
    printf("    Class: %s\n", get_class(dev->class));
    printf("    Speed: %s\n", get_speed(dev->speed));
}

void print_devs()
{
    for (int i = 0; i < dev_id; i++) {
        print_device(i);
    }
}