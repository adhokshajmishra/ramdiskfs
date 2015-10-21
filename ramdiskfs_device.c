#include <linux/types.h>
#include <linux/vmalloc.h>
#include <linux/string.h>
#include <linux/errno.h>

#include "ramdiskfs.h"
#include "partition.h"

#define RB_DEVICE_SIZE 10240 /* sectors */
/* So, total device size = 10240 * 512 bytes = 5 MiB */

/* Array where the disk stores its data */
static u8 *dev_data;

int ramdiskfs_init(void)
{
	dev_data = vmalloc(RB_DEVICE_SIZE * RB_SECTOR_SIZE);
	if (dev_data == NULL)
		return -ENOMEM;
	/* Setup its partition table */
	copy_mbr_n_br(dev_data);
	return RB_DEVICE_SIZE;
}

void ramdiskfs_cleanup(void)
{
	vfree(dev_data);
}

void ramdiskfs_write(sector_t sector_off, u8 *buffer, unsigned int sectors)
{
	memcpy(dev_data + sector_off * RB_SECTOR_SIZE, buffer,
		sectors * RB_SECTOR_SIZE);
}
void ramdiskfs_read(sector_t sector_off, u8 *buffer, unsigned int sectors)
{
	memcpy(buffer, dev_data + sector_off * RB_SECTOR_SIZE,
		sectors * RB_SECTOR_SIZE);
}
