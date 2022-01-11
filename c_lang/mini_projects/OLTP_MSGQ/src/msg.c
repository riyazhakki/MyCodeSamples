# include <sys/types.h>
# include <sys/msg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>

# include "dbase.h"
# include "sb.h"

static int NOT_RECEIVED;

int send_message (int msgd, void * message, int size ){
	int pid;

	get_pid ( &pid );
	while ( NOT_RECEIVED ) {
		printf ( "Wating for previous reply...\r" );
		fflush ( stdout );
	}

	if ( msgsnd ( msgd, message, size, IPC_NOWAIT ) != -1 ) {
		kill ( pid, SIGUSR2 );
	}
}
 
int receive_message (int msgd, void * message, int size, int type) {
	int pid;

	get_pid ( &pid );
	while ( msgrcv ( msgd, message, size, type, IPC_NOWAIT ) == -1 ) {
		kill ( pid, SIGUSR2 );
		printf ("\033[5mPLEASE WAIT...\r\033[0m" );
		fflush ( stdout );
		NOT_RECEIVED = 1;
		sleep ( 1 );
	}
	NOT_RECEIVED = 0;
}

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
