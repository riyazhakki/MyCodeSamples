# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>

main ( ) {
	int fd;
	int pid;

	fd = open ( "filepid", O_RDONLY );

	if ( fd < 0 ){
		fprintf ( stderr, "ERROR IN FILE...\n" );
		exit (1);
	}

	read ( fd, &pid, sizeof (pid) );
	printf ( "pid: %d\n", pid );

	kill ( pid, SIGUSR1 );
}
