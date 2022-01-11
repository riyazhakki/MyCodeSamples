# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>

main () {
	int fd;
	int pid = 1;
	int var;
	char filename [ 20 ];
	
	sprintf ( filename, "../dbase/sbd_%d", getuid ( ) );
	fd = open ( filename, O_RDONLY, 0744 );

	if ( fd < 0 ) {
		fprintf ( stderr, "Error in file opening...\n" );
		exit ( 1 );
	}

	read ( fd, &pid, sizeof(pid) );
	close (fd);

	kill ( pid, SIGUSR1 );
	return 0;
}
