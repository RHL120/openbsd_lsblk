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
install: all
	cp ./lsblk /usr/bin/lsblk
sinstall: all
	echo "installing with setuid. I wouldn't trust it"; cp ./lsblk /usr/sbin/lsblk && chmod +s /usr/sbin/lsblk
