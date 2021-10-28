#include <stdio.h>
#include <unistd.h>
#include "prints.h"

int main(int argc, char *argv[]) {

	puts(table_head);
	if (geteuid()) {
		fprintf(stderr, "Permssion denied\n");
		return -1;
	}
	long mntsize;
	struct statfs *mntbuf;
	mntsize = getmntinfo(&mntbuf, MNT_NOWAIT);
	for (int i = 0; i <= 9; i++) {
		struct disklabel dl;
		char *dname;
		int ret = get_disk_info (i, &dl, &dname);
		if (ret == -1) {
			continue;
		} else if (ret == -2) {
			fprintf(stderr, "Something went worng\n");
			return -2;
		}
		struct size_unit su = convert_size(DL_GETDSIZE (&dl));
		printf ("%s\t\t%.1f%c\n", dname, su.size, su.unit);
		for (unsigned char i = 0; i < dl.d_npartitions; ++i) {
			print_partition(&dl, i, mntbuf, mntsize, dname);
		}
		free (dname);
	}
}
