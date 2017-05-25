/*ex12_timestamp.c: Treat the command line arguments as pathnames use stat(2) system call and print their timestamps Do ls -l and compare your outputs. */

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <time.h>

main (int argc, char* argv [ ] ) {

struct stat st_buf;
struct tm ftime;

	if ( argc < 2 ) {
		fprintf ( stderr, "Filename not given....\n" );
		exit ( 1 );
	}

	if ( (stat ( argv [1], &st_buf )) < 0 ) {
		fprintf ( stderr, "Error in stat %s...!\n", argv [1] );
		exit ( 2 );
	}

	printf ( "Creation time: %s", ctime (&st_buf.st_ctime) );
	printf ( "Modified time: %s", ctime (&st_buf.st_mtime) );
	printf ( "Access time:   %s", ctime (&st_buf.st_atime) );

}
