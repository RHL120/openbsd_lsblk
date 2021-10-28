#ifndef PRINTSH
#define PRINTSH
#include <stdlib.h>
#include "disk.h"
extern const char *table_head;
struct size_unit {
	double size;
	char unit;
};
struct size_unit convert_size (size_t size);


void print_partition(struct disklabel *dp, unsigned char i, struct statfs *mntbuf, long mntsize, char *dname);

/*It's ok here to not return a pointer because sizeof(struct size_unit) is small */
struct size_unit convert_size (size_t size);
#endif
