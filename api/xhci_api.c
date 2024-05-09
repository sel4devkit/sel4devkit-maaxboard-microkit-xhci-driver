#include <sddf/blk/shared_queue.h>
#include <stdint.h>
#include <xhci_api.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

uintptr_t umass_free;
uintptr_t umass_used;
extern blk_queue_handle_t *umass_buffer_ring;

// buffers for devices
extern uintptr_t kbd_free;
extern uintptr_t kbd_used;
extern uintptr_t mse_free;
extern uintptr_t mse_used;
extern uintptr_t uts_free;
extern uintptr_t uts_used;
extern struct blk_resp_queue* umass_resp;
extern struct blk_req_queue* umass_req;

static int current_xfer = -1;
struct umass_request *active_xfer;

ring_handle_t *usb_new_device_ring;
uintptr_t usb_new_device_free;
uintptr_t usb_new_device_used;

int umass_id = 0;
int num_devices = 0;
struct sel4_usb_device* usb_devices[MAX_DEVICES];

int execute_next(struct sel4_usb_device*,struct umass_request*);

/**
 * api_init(): initialise structures required by api
*/
void api_init(ring_handle_t **kbd, ring_handle_t **mse, ring_handle_t **uts, blk_queue_handle_t **umass) {
    *kbd = (ring_handle_t*) malloc(sizeof(ring_handle_t));
    ring_init(*kbd, (ring_buffer_t *)kbd_free, (ring_buffer_t *)kbd_used, NULL, 0);
    *mse = (ring_handle_t*) malloc(sizeof(ring_handle_t));
    ring_init(*mse, (ring_buffer_t *)mse_free, (ring_buffer_t *)mse_used, NULL, 0);
    *uts = (ring_handle_t*) malloc(sizeof(ring_handle_t));
    ring_init(*uts, (ring_buffer_t *)uts_free, (ring_buffer_t *)uts_used, NULL, 0);
    *umass = (blk_queue_handle_t*) malloc(sizeof(blk_queue_handle_t));
    blk_queue_init(*umass, umass_req, umass_resp, false, BLK_REQ_QUEUE_SIZE, BLK_RESP_QUEUE_SIZE);

    // New device event ring
    usb_new_device_ring = malloc(sizeof(*usb_new_device_ring));
    ring_init(usb_new_device_ring, (ring_buffer_t *)usb_new_device_free, (ring_buffer_t *)usb_new_device_used, NULL, 0);
}

int enqueue_umass_request(int dev_id, bool read, int blkno, int nblks, void* val, void* cb) {
    struct sel4_usb_device *dev = usb_devices[dev_id];
    if (!(dev->class == 0 && dev->ifaceClass == 0x8)) {
        printf("Device %d is not a mass storage device\n", dev_id);
        return -1;
    }

    int xfer_id = ++current_xfer;
    struct umass_request* umass_xfer = (struct umass_request*) malloc(sizeof(struct umass_request));

    umass_xfer->dev_id = dev->id;
    umass_xfer->umass_id = dev->umass_dev->umass_id;
    umass_xfer->read = read;
    umass_xfer->blkno = blkno;
    umass_xfer->nblks = nblks;
    umass_xfer->complete = false;
    umass_xfer->val = val;
    umass_xfer->cb = cb;
    umass_xfer->xfer_id = xfer_id;

    // ensure reads and writes are executed in the order they arrived
    if (!dev->umass_dev->locked) {
        // dev->umass_dev->locked = true;
        umass_buffer_ring->req_queue->in_progress = true;
        execute_next(dev, umass_xfer);
        while (umass_buffer_ring->req_queue->in_progress) { // poll for complete transfer
            printf("sleeping on xfer %d\n", xfer_id);
            seL4_Yield();
        }
        // handle_xfer_complete();

        int id;
        uint16_t count, success_count;
        uintptr_t addr;
        blk_response_status_t status;
        blk_dequeue_resp(umass_buffer_ring, &status, &addr, &count, &success_count, &id);
        dev->umass_dev->locked = false;
        return 1;
    } else {
        printf("device busy\n");
    }



    return xfer_id;
}

int execute_next(struct sel4_usb_device* dev, struct umass_request* xfer) {
    // printf("xfer_id: %i    blkno: %i    nblks: %i\n", xfer->xfer_id, xfer->blkno, xfer->nblks);

    blk_request_code_t code = WRITE_BLOCKS;
    if (xfer->read)
        code = READ_BLOCKS;
    blk_enqueue_req(umass_buffer_ring, code, (uintptr_t) xfer->val, xfer->blkno, xfer->nblks, xfer->xfer_id);
    microkit_notify(47);

    return xfer->xfer_id;
}

int get_blksize(int dev_id) {
    struct sel4_usb_device* dev = usb_devices[dev_id];
    if (dev->class == 0)
        if (dev->ifaceClass == 0x8)
            return dev->umass_dev->dev_info.blocksize;
    return -1;
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
    }
}

char* get_class(int class) {
    switch(class) {
        case 0: 
            return "Device";
        case 1: 
            return "Audio";
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
        printf("%i: %s,\tUSB Revision %x.%x\n", dev->id, get_class(dev->ifaceClass), (dev->rev>>8)&0xff, (dev->rev>>0)&0xff);
    else
        printf("%i: %s,\tUSB Revision %x.%x\n", dev->id, get_class(dev->class), (dev->rev>>8)&0xff, (dev->rev>>0)&0xff);
    if (dev->serial)
        printf(" - %s %s (serial %s)\n", dev->vendor, dev->product, dev->serial);
    else
        printf(" - %s %s\n", dev->vendor, dev->product);
    printf(" - Vendor: 0x%04x Product: 0x%04x\n", dev->vendorid, dev->productid);
    printf(" - PacketSize: %d Configurations: %d\n", (int) dev->mps, dev->num_configs);
    if (dev->class == 0)
        printf(" - Class: (from interface) %s\n", get_class(dev->ifaceClass));
    else
        printf(" - Class: %s\n", get_class(dev->class));
    printf(" - Speed: %s\n", get_speed(dev->speed));
    if (dev->class == 0) {
        printf(" - Interface info\n");
        printf("    - Class: %s\n", get_class(dev->ifaceClass));
    }
    printf(" - Depth: %d\n", dev->depth);
    if (dev->class == 0) {
        if (dev->ifaceClass == 0x08) {
            printf(" - Mass storage info\n");
            printf("    - umass id %d (serial %s): %llu (blocks) \n", dev->umass_dev->umass_id, dev->umass_dev->dev_info.serial_number, dev->umass_dev->dev_info.size*dev->umass_dev->dev_info.blocksize);
		    printf("    - %d cyl, %d head, %d blocks, %llu blk size\n", dev->umass_dev->dev_info.cylinders, dev->umass_dev->dev_info.heads, dev->umass_dev->dev_info.blocks, dev->umass_dev->dev_info.blocksize);
        }
    }
}

void print_devs()
{
    for (int i = 0; i <= num_devices; i++) {
        print_device(i);
        printf("\n");
    }
}
