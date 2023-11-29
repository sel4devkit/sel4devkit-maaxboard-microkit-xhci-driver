#include <stddef.h>
#include <stdbool.h>

#define INIT            44
#define KEYBOARD_EVENT  45
#define MOUSE_EVENT     46
#define UMASS_COMPLETE  48

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

void umass_api_init();
void handle_xfer_complete();

/**
 * @param dev_id: id of device to request
 * @param read true for read, false for write
 * @param blkno starting block number for request
 * @param nblks number of blocks requested
 * @param val   read: address to write response
 *              write: blocks to write to device
 * @param cb function to call on transfer completion (optional)
 * 
 * @return transaction id on success, -1 on failure
*/
int enqueue_umass_request(int dev_id, bool read, int blkno, int nblks, void* val, void* cb);