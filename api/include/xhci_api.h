#ifndef _XHCI_API_
#define _XHCI_API_

#include <stddef.h>
#include <stdbool.h>
#include <shared_ringbuffer/shared_ringbuffer.h>
#include <sddf/blk/shared_queue.h>

//USB definitions (from netbsd usb.h)
#define USB_SPEED_LOW           1
#define USB_SPEED_FULL          2
#define USB_SPEED_HIGH          3
#define USB_SPEED_SUPER         4
#define USB_SPEED_SUPER_PLUS    5
#define MAX_DEVICES 127

// Channel IDs
#define NEW_DEVICE_EVENT        45
#define KEYBOARD_EVENT          46
#define MOUSE_EVENT             48
#define UMASS_COMPLETE          49
#define TOUCHSCREEN_EVENT       50
#define UMASS_COMPLETE_1        51

#define INIT                    60

struct umass_request;
extern int num_devices;

typedef void (*umass_cb)(struct umass_request *);

struct umass_request{
    int dev_id;     /* device id */
    int umass_id;   /* umass id */
    bool read;      /* r = 1 | w = 0 */
    int blkno;      /* start block */
    int nblks;      /* num of blocks */
    void* val;      /* write value, or address for read return */
    bool complete;  /* is xfer complete (for sync transfers) */
    umass_cb cb;    /* callback */
    int xfer_id;    /* xfer id */
};

struct sel4_umass_device {
    int umass_id;                       /* umass id */
    bool locked;                        /* mutex */
    ring_handle_t *api_request_ring;    /* xfer queue */

    blk_storage_info_t dev_info;
};

struct sel4_usb_device {
    int id;                                 /* device id */
    char* vendor;                           /* vendor string */
    char* product;                          /* product string */
    char* serial;                           /* product serial */
    int vendorid;                           /* vendor hex code */
    int productid;                          /* product hex code */
    int class;                              /* class of device (if 0, check interface) */
    int subclass;                           /* subclass of device */
    int ifaceClass;                         /* interface class */
    int ifaceSub;                           /* interface sub class */
    int depth;                              /* how many connections from HC device is */
    int speed;                              /* speed of device */
    int protocol;                           /* USB protocol */
    int mps;                                /* max packet size */
    int len;                                /* length of packet */
    int num_configs;                        /* number of configs */
    int rev;                                /* USB revision */
    struct sel4_umass_device *umass_dev;    /* mass storage specific information */
};

/**
 * Initialises required data structures for api
*/
void api_init(ring_handle_t **kbd, ring_handle_t **mse, ring_handle_t **uts, blk_queue_handle_t **umass);

/**
 * Handles callback from complete mass storage API request
*/
void handle_xfer_complete();

/**
 * Handles new device connection
*/
void handle_new_device();

/**
 * Enqueues new request to device
 * 
 * @param dev_id id of device to request
 * @param read true for read, false for write
 * @param blkno starting block number for request
 * @param nblks number of blocks requested
 * @param val   read: address to write response
 *              write: blocks to write to device
 * @param cb function to call on transfer completion (optional). Function should take struct umass request as input.
 * 
 * @return transaction id on success, -1 on failure
*/
int enqueue_umass_request(int dev_id, bool read, int blkno, int nblks, void* val, void* cb);

/**
 * Prints device info to debug
 * 
 * @param dev_id id of device to print
 * 
 * @return none
*/
void print_device(int dev_id);

/**
 * Print all devices to debug
*/
void print_devs();

/**
 * Get blocksize of device (returns -1 if not mass storage dev)
*/
int get_blksize(int);

#endif /* XHCI_API */
