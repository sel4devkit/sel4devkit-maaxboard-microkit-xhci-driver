#include <stddef.h>
#include <stdbool.h>

//USB definitions
#define USB_SPEED_LOW           1
#define USB_SPEED_FULL          2
#define USB_SPEED_HIGH          3
#define USB_SPEED_SUPER         4
#define USB_SPEED_SUPER_PLUS    5

#define INIT                    44
#define KEYBOARD_EVENT          45
#define MOUSE_EVENT             46
#define UMASS_COMPLETE          48
#define TOUCHSCREEN_EVENT       49
#define NEW_DEVICE_EVENT        50

#define MAX_DEVICES 127

struct umass_request;

typedef void (*umass_cb)(struct umass_request *);

struct umass_request{
    int dev_id; // dev id
    bool read; // r = 1 / w = 0
    int blkno; //start block
    int nblks; // num of blocks
    void* val; // write value, or null for read
    umass_cb cb; // callback
    int xfer_id; // xfer id
};

struct usb_new_device{
    int id; // device id
    char* vendor;
    char* product;
    int vendorid;
    int productid;
    int class;
    int speed;
};

/**
 * Initialises required rings for mass storage part of api
*/
void umass_api_init();

/**
 * Handles callback from complete API
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
