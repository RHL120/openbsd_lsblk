#include <stdio.h>
#include <sys/disklabel.h>
#include <string.h>
#include <sys/types.h>
#include <sys/mount.h>
#include <util.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/dkio.h>
int get_disk_info(unsigned char number, struct disklabel *dlp, char **dnamep) {
	char diskname[5];
	snprintf(diskname, 4, "sd%d", number);
	char *rp;
	int diskfd = opendev(diskname, O_RDONLY, OPENDEV_PART, &rp);
	if (diskfd < 0) {
		return -1;
	}
	if (ioctl(diskfd, DIOCGDINFO, dlp) == -1) {
		close (diskfd);
		return -2;
	}
	close (diskfd);
	//malloc here to a void mallocing on drives that don't exists and to avoid frees.
	*dnamep = strndup (diskname, 4);
	return 0;
}

char *get_mount_point(const char *name, struct statfs *mntbuf, long mntsize) {
	for (int i = 0; i < mntsize; i++) {
		if (!strcmp(mntbuf[i].f_mntfromname, name))
			return mntbuf[i].f_mntonname;
	}
	return 0;
}
