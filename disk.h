#ifndef DISKSH
#define DISKSH
#include <sys/types.h>
#include <sys/disklabel.h>
#include <sys/mount.h>
#include <sys/swap.h>
int get_disk_info(unsigned char number, struct disklabel *dlp, char **dnamep);
const char *get_mount_point(const char *name, const struct statfs *mntbuf, long mntsize, const struct swapent *swapbuf, int swapsize);
void print_disk(const struct statfs *mntbuf, size_t mntsize, const struct swapent *swapbuf, int swapsize, uint8_t diskn);
int get_swap(struct swapent **ret);
#endif
