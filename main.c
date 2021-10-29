#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "prints.h"

//Kind of like lsblk on linux but for openBSD an without the feilds that
//no one cares about
int main(int argc, char *argv[]) {
	if (geteuid()) {
		fputs (err_perm, stderr);
		return -1;
	}
	long mntsize;
	//the reason why we have to define mntbuf and swapbuff here is because
	//I think calling these functions is too slow to do every time we loop
	struct statfs *mntbuf;
	mntsize = getmntinfo(&mntbuf, MNT_NOWAIT);
	struct swapent *swapbuff;
	int swapsize = get_swap(&swapbuff);
	if (swapsize < 0) {
		fputs(err_lazy, stderr);
		return -2;
	}
	puts(table_head);
	if (argc >= 2) {
		for (int i = 1; i < argc; ++i) {
			if (strlen (argv[i]) == 3 && !strncmp(argv[i], "sd", 2)) {
				const char *errstr;
				//Is it safe to do this conversion?
				u_int8_t dn = strtonum(argv[i] + 2, 0, 9, &errstr);
				if (errstr) {
					fprintf (stderr, err_diskname, argv[i]);
				} else {
					print_disk(mntbuf, mntsize,swapbuff, swapsize, dn);
				}
			} else {
				fprintf (stderr, err_diskname, argv[i]);
			}
		}
	} else {
		for (int i = 0; i <= 9; i++) {
			print_disk(mntbuf, mntsize, swapbuff, swapsize,  i);
		}
	}
	free (swapbuff);
}
