#ifndef ramdiskfs_H
#define ramdiskfs_H

#define RB_SECTOR_SIZE 512

extern int ramdiskfs_init(void);
extern void ramdiskfs_cleanup(void);
extern void ramdiskfs_write(sector_t sector_off, u8 *buffer, unsigned int sectors);
extern void ramdiskfs_read(sector_t sector_off, u8 *buffer, unsigned int sectors);
#endif
