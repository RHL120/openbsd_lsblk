#ifndef DISKSH
#define DISKSH
#include <sys/types.h>
#include <sys/disklabel.h>
#include <sys/mount.h>
#include <sys/swap.h>

extern const char *swap_mntp;

//Sets dlp to be disklabel and dnamep to be "sd{number}" and returns -1 on error
//and 0 otherwise
int get_disk_info(unsigned char number, struct disklabel *dlp, char **dnamep);
//return the mountpoint of a disk if one is found. if the disk is used for swap
//it returns swap_mntp
const char *get_mount_point(const char *name, const struct statfs *mntbuf, long mntsize, const struct swapent *swapbuf, int swapsize);
//sets ret to be a list of struct swapent and return -1 on error and 0 otherwise
int get_swap(struct swapent **ret);
#endif
