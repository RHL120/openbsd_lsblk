#include <stdio.h>
#include "prints.h"
#include "disk.h"
const char *table_head = "NAME\t\tSIZE\t\tTYPE\t\tMOUNTPOINT";

/*It's ok here to not return a pointer because sizeof(struct size_unit) is small */
struct size_unit convert_size (size_t size) {
	struct size_unit su;
	if (size >= 2097152) {
		su.size =  (double)size / 2097152;
		su.unit =  'G';
	} else if (size >= 1048576) {
		su.size = (double)size / 1048576;
		su.unit = 'M';
	} else if (size >= 1024) {
		su.size = (double)size / 1024;
		su.unit = 'K';
	} else {
		su.unit = 'b';
		su.size = size;
	}
	return su;
}


void print_partition(struct disklabel *dp, unsigned char i, struct statfs *mntbuf, long mntsize, char *dname) {
	unsigned char part_letter = 'a' + i;
	unsigned long size = DL_GETPSIZE(&dp->d_partitions[i]);
	if (size && part_letter != 'c') {
		char dp[11];
		snprintf(dp, 10, "/dev/%s%c", dname, part_letter);
		struct size_unit su = convert_size(size);
		char *mntp = get_mount_point(dp, mntbuf, mntsize);
		if (!mntp) {
			printf ("|-%s%c\t\t%.1f%c\t\tpart\n", dname, part_letter,
					su.size, su.unit);
		} else {
			printf ("|-%s%c\t\t%.1f%c\t\tpart\t\t%s\n", dname,
					part_letter, su.size, su.unit, mntp);
		}
	}
}

void print_disk(struct statfs *mntbuf, size_t mntsize, uint8_t diskn) {
		struct disklabel dl;
		char *dname;
		int ret = get_disk_info (diskn, &dl, &dname);
		if (ret == -1) {
			return;
		} else if (ret == -2) {
			fprintf(stderr, "Something went worng\n");
			return;
		}
		struct size_unit su = convert_size(DL_GETDSIZE (&dl));
		printf ("%s\t\t%.1f%c\t\tdisk\n", dname, su.size, su.unit);
		for (unsigned char i = 0; i < dl.d_npartitions; ++i) {
			print_partition(&dl, i, mntbuf, mntsize, dname);
		}
		free (dname);
}
