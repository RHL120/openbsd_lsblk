#include <stdio.h>
#include <string.h>
#include <util.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/dkio.h>
#include <unistd.h>
#include <stdlib.h>
#include "disk.h"

//This is a global variable because I do not want to have to strdup("[ swap ]")
//It can be static though I guess...
const char *swap_mntp = "[ SWAP ]";

int get_disk_info(unsigned char num, struct disklabel *dst_dl, char **dst_name) {
	char diskname[5];
	snprintf(diskname, 4, "sd%d", num);
	char *rp;
	int diskfd = opendev(diskname, O_RDONLY, OPENDEV_PART, &rp);
	if (diskfd < 0) {
		return -1;
	}
	if (ioctl(diskfd, DIOCGDINFO, dst_dl) == -1) {
		close (diskfd);
		return -2;
	}
	close (diskfd);
	//malloc here to a void mallocing on drives that don't exists and to avoid frees.
	*dst_name = strndup (diskname, 4);
	return 0;
}

int get_swap(struct swapent **ret) {
	struct swapent *swapbuff;
	int swapsize = swapctl(SWAP_NSWAP, NULL, 0);
	swapbuff = calloc (swapsize, sizeof(struct swapent));
	if (!swapbuff) {
		*ret = NULL;
		return -1;
	}
	// TODO: write a better comment bellow lol
	//the return value could be different re-assign to avoid overflows
	//if ret < swapsize (sizeof(swapbuff)) < swapsize it could overflow.
	swapsize = swapctl(SWAP_STATS, swapbuff, swapsize);
	*ret = swapbuff;
	return swapsize;
}

const char *get_mount_point(const char *disk_path, const struct statfs *mntbuf, long mntsize, const struct swapent *swapbuf, int swapsize) {
	for (int i = 0; i < mntsize; i++) {
		if (!strcmp(mntbuf[i].f_mntfromname, disk_path))
			return mntbuf[i].f_mntonname;
	}
	for (int i = 0; i < swapsize; i++) {
		if (!strcmp(swapbuf[i].se_path, disk_path)) {
			return swap_mntp;
		}
	}
	return 0;
}
