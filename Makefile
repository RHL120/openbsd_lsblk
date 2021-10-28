all: main disk prints
	cc -o lsblk main.o disk.o prints.o -lutil
main:
	cc -c main.c
disk:
	cc -c disk.c disk.h
prints:
	cc -c prints.c prints.h
clean:
	rm *.o *.gch lsblk
install:
	cp ./lsblk /usr/sbin/lsblk
sinstall:
	echo "installing with setuid. I wouldn't trust it"; cp ./lsblk /usr/sbin/lsblk
