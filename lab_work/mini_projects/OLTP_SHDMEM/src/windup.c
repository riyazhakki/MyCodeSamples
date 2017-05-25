/* Windup amount */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/msg.h>
# include <fcntl.h>
# include "dbase.h"

main ( int argc, char *argv [ ] ) {

	int size;
	int shmd;
	int from_server;
	int to_server;
	int pid;

	struct message *message;

	shmd = shmget ( (key_t) getuid ( ), 100, 0600 );
	message = (struct message *) shmat ( shmd, 0, 0 );

	to_server 	= atoi ( argv [ 1 ] );
	from_server = atoi ( argv [ 2 ] );

	message [MASTER_REQUEST].type	= to_server;
	message [ to_server ].transaction.windup.type = WINDUP; 
	message [ to_server ].status = IDLE;

	get_pid ( &pid );
	while ( message [ to_server ].status != WRITTEN ) {
		message [to_server].status = IDLE;
		printf ( "Waiting windup reply...\r");
		fflush ( stdout );
		kill ( pid, SIGUSR2 );
	}
	message [ to_server ].status = IDLE;

	if ( message [from_server].transaction.windup_reply.result == SUCCESS ) {
		printf (" TRANSACTION SUCCESSFULL.\n" );
	}	
}
