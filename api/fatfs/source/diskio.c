/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */
#include <xhci_api.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Definitions of physical drive number for each drive */
#define DEV_RAM		0	/* Example: Map Ramdisk to physical drive 0 */
#define DEV_MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
#define DEV_USB		2	/* Example: Map USB MSD to physical drive 2 */

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	int result;

	switch (pdrv) {
	case DEV_USB :
		// result = USB_disk_status();
		result = 0;

		// translate the reslut code here

		return stat = 0;
	}
	return 0;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	int result;

    pdrv = 2;
	switch (pdrv) {
	case DEV_USB :
		// result = USB_disk_initialize();
		result = 1;

		// translate the reslut code here
		stat = 0;

		return RES_OK;
	}
    printf("NO INIT %d\n", pdrv);
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res;
	int result;

    pdrv  = 2;
	BYTE *temp_buff = calloc(count*512, 1);
	switch (pdrv) {
	case DEV_USB :
		// translate the arguments here

		result = enqueue_umass_request(5, true, sector, count, temp_buff, NULL);
		memcpy(buff, temp_buff, count*512); // dump buffer in shared mem

		// translate the result code here
		if (result == -1)
			res = RES_ERROR;
		else
			res = RES_OK;

		return res;
	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res;
	int result;

	pdrv = 2;
	BYTE *temp_buff = calloc(count*512, 1);
	switch (pdrv) {
	case DEV_USB :
		// translate the arguments here
		memcpy(temp_buff, buff, count*512); // dump buffer in shared mem
		result = enqueue_umass_request(5, false, sector, count, temp_buff, NULL);

		// translate the result code here
		if (result == -1)
			res = RES_ERROR;
		else
			res = RES_OK;
		return res;
	}

	return RES_PARERR;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
	int result;

	switch (pdrv) {
	case DEV_USB :

		// Process of the command the USB drive
		if (cmd & CTRL_SYNC) {
			/* HEXDUMP("ioctl buff\n", buff, sizeof(*buff)); */
			return RES_OK;
		}

		return res;
	}

	return RES_PARERR;
}

