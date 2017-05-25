# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>

main () {
struct stat stbuf;
stat (".", &stbuf );
printf ("%d\n", stbuf.st_ino);
}
