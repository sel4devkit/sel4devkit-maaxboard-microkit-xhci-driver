/*	$NetBSD: usb_mem.h,v 1.37 2022/03/03 06:09:11 riastradh Exp $	*/
/*	$FreeBSD: src/sys/dev/usb/usb_mem.h,v 1.9 1999/11/17 22:33:47 n_hibma Exp $	*/

/*
 * Copyright (c) 1998 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Lennart Augustsson (lennart@augustsson.net) at
 * Carlstedt Research & Technology.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef	_DEV_USB_USB_MEM_H_
#define	_DEV_USB_USB_MEM_H_

#include <sys/types.h>
#include <evbarm/types.h>

#include <sys/bus.h>
#include <sys/queue.h>

#include <dev/usb/usbdivar.h>
#include <evbarm/bus_defs.h>

typedef struct arm32_bus_dmamap		*bus_dmamap_t;

typedef struct usb_dma_block {
	bus_dma_tag_t tag;
	bus_dmamap_t map;
	void *kaddr;
	bus_dma_segment_t *segs;
	int nsegs;
	int nsegs_alloc;
	size_t size;
	size_t align;
	int flags;
#define USB_DMA_FULLBLOCK	__BIT(0)
#define USB_DMA_COHERENT	__BIT(1)

	LIST_ENTRY(usb_dma_block) next;
} usb_dma_block_t;

#define USBMALLOC_MULTISEG	__BIT(0)
#define USBMALLOC_COHERENT	__BIT(1)
#define USBMALLOC_ZERO		__BIT(2)

int		usb_allocmem(bus_dma_tag_t, size_t, size_t, u_int, usb_dma_t *);
void		usb_freemem(usb_dma_t *);
void		usb_syncmem(usb_dma_t *, bus_addr_t, bus_size_t, int);

bus_addr_t	usb_dmaaddr(usb_dma_t *, unsigned int);

void *temp_kernaddr(usb_dma_t *, unsigned int);

// void *temp_kernaddr(usb_dma_t *dma, unsigned int o) {
// 	void *ptr = (void *)(usb_dmaaddr((dma), (o)));
// 	printf("&kernaddr %x, kernaddr %x\n", &ptr, ptr);
// 	return ptr;
// }
// #define DMAADDR(dma, o)	usb_dmaaddr((dma), (o))
#define DMAADDR(dma, o)	((bus_addr_t) getPhys((void*) usb_dmaaddr((dma), (o))))
#define KERNADDR(dma, o) (void *) (usb_dmaaddr((dma),(o)))

// #define KERNADDR(dma, o) \
// 	((void *)((char *)(dma)->udma_block->kaddr + (dma)->udma_offs + (o)))

#endif	/* _DEV_USB_USB_MEM_H_ */
