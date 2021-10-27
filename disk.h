int get_disk_info(unsigned char number, struct disklabel *dlp, char **dnamep);
char *get_mount_point(const char *name, struct statfs *mntbuf, long mntsize);
