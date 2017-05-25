/* Windup amount */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/msg.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "dbase.h"

main ( int argc, char *argv [ ] ) {

	int size;
	int shmd;
	int pid;
	int fdmreq, fdwrep;
	int red;
	extern int errno;
	struct windup windup;
	struct windup_reply windup_reply;

	windup.type = WINDUP;
	strcpy ( windup.to_server,   argv [ 1 ] );
	strcpy ( windup.from_server, argv [ 2 ] );

	fdmreq = open ( "MASTER_REQUEST",   O_NONBLOCK | O_WRONLY );
	fdwrep = open ( windup.from_server, O_NONBLOCK | O_RDONLY );

	write ( fdmreq, &windup, sizeof (windup) );
	get_pid ( &pid );
	red = read ( fdwrep, &windup_reply, sizeof (windup_reply) );

	while ( ( (red< 0) && (errno == EAGAIN) ) || (red == 0) ) {
		red = read ( fdwrep, &windup_reply, sizeof (windup_reply) );
		printf ( "Waiting windup reply...\r");
		fflush ( stdout );
		kill ( pid, SIGUSR2 );
	}

	if ( windup_reply.result == SUCCESS ) {
		printf (" TRANSACTION SUCCESSFULL.\n" );
	}	
}
