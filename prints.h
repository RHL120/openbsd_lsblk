#ifndef PRINTSH
#define PRINTSH
#include <stdlib.h>
#include "disk.h"

extern const char *table_head;

struct size_unit {
	double size;
	char unit;
};

//It's ok here to not return a pointer because sizeof(struct size_unit) is small
//convert a size to it's best looking unit
struct size_unit convert_size (size_t size);
//prints the info found in args according table_head with a |- before NAME
void print_partition(const struct disklabel *dp, unsigned char i, const struct statfs *mntbuf, long mntsize, const struct swapent *swapbuf, int swapsize, char *dname);
//prints the info found in args according table_head
void print_disk(const struct statfs *mntbuf, size_t mntsize, const struct swapent *swapbuf, int swapsize, uint8_t diskn);
#endif
