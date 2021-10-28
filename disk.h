#ifndef DISKSH
#define DISKSH
#include <sys/types.h>
#include <sys/disklabel.h>
#include <sys/mount.h>
int get_disk_info(unsigned char number, struct disklabel *dlp, char **dnamep);
char *get_mount_point(const char *name, struct statfs *mntbuf, long mntsize);
#endif
