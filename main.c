#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "prints.h"

int main(int argc, char *argv[]) {
	if (geteuid()) {
		fprintf(stderr, "Permssion denied\n");
		return -1;
	}
	puts(table_head);
	long mntsize;
	struct statfs *mntbuf;
	mntsize = getmntinfo(&mntbuf, MNT_NOWAIT);
	if (argc >= 2) {
		for (int i = 1; i < argc; ++i) {
			if (!strncmp(argv[i], "sd", 2)) {
				const char *errstr;
				//Is it safe to do this conversion?
				u_int8_t dn = strtonum(argv[i]+2, 0, 9, &errstr);
				if (errstr) {
					fprintf (stderr,
							"%s is not a vaild disk\n",
							argv[i]);
				} else {
					print_disk(mntbuf, mntsize, dn);
				}
			} else {
				fprintf (stderr, "%s is not a disk!\n", argv[i]);
			}
		}
	} else {
		for (int i = 0; i <= 9; i++) {
			print_disk(mntbuf, mntsize, i);
		}
	}
}
