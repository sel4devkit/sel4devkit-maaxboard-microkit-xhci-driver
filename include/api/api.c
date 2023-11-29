#include <api.h>
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

/**
 * umass_api_init(): initialise rings required by api
*/
void umass_api_init() {
    api_request_ring = kmem_alloc(sizeof(ring_buffer_t), 0);
    umass_free = kmem_alloc(0x200000, 0);
    umass_used = kmem_alloc(0x200000, 0);
    ring_init(api_request_ring, (ring_buffer_t *)umass_free, (ring_buffer_t *)umass_used, NULL, 1);
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

    enqueue_used(api_request_ring, umass_xfer, sizeof(umass_xfer), (void*)0);

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
    if (!driver_dequeue(api_request_ring->used_ring, (uintptr_t**)&buffer, &len, &cookie)) {
        struct umass_request* xfer = (struct umass_request*)buffer; 
        printf("xfer_id: %i    blkno: %i    nblks: %i\n", xfer->xfer_id, xfer->blkno, xfer->nblks);
        active_xfer = xfer;

        bool empty = ring_empty(umass_buffer_ring);
        int error = enqueue_used(umass_buffer_ring, (uintptr_t) xfer, sizeof(xfer), (void *)0);
        if (empty)
            microkit_notify(47);

        return xfer->xfer_id;
    } else {
        return -1;    
    }
}

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