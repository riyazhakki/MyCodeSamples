# include <stdio.h>
# include <fcntl.h>

int get_pid ( int *pid  ) {

	int fd;
	char filename [20];

	sprintf ( filename, "../dbase/sbd_%d", getuid ( ) );
	fd = open ( filename,  O_RDWR );
	if ( fd < 0 ) return ( -1 );
	read ( fd, pid, sizeof ( *pid ) ); 
	close ( fd );
	return ( 0 );
}
