# openbsd_lsblk
Many ex-linux users (new OpenBSD users) complain about the lack of an lsblk like command (even though diskname + swapctl + df can do what lsblk does) I happen to
like lsblk so I decided to write a version of it for OpenBSD.

## Diffrences from linux's lsblk
1) It doesn't list major and minor numbers (because I never really used them)
2) It needs su or setuid (becuase disklabel is the only lib I found and it needs su)
3) It uses ascii chars only
4) It doesn't take any flags. It's only (optional) arg is a diskname (ex: sd0)
5) It doesn't list CDs
## Installation
```bash
git clone https://github.com/RHL120/openbsd_lsblk.git
cd openbsd_lsblk
make
doas make install #You can do make sinstall to put it in /usr/local/sbin and to set suid but I don't recommend it because it may have bugs
make clean
```
## Contributing
I hope you enjoy using it but please if you can take a look at the source code and see if you can help with making it better.
