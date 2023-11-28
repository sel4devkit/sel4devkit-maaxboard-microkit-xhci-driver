#include <stddef.h>
#include <stdbool.h>

// struct {
// 	int dx, dy, dz, dw;
// 	uint32_t buttons = 0;
// } mouse_event;

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

// struct umass_packet{
//     int dev_id; // dev id
//     bool read; // r = 1 / w = 0
//     int blkno; //start block
//     int nblks; // num of blocks
//     void* val; // write value, or null for read
// }

void umass_api_init();

void handle_xfer_complete();

