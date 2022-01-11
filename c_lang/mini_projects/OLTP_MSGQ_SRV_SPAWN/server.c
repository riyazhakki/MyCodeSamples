/****server.c****/

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <sys/ipc.h>
# include <sys/msg.h>
# include <sys/sem.h>
# include <sys/types.h>

# include "dbase.h"
# include "msg.h"

extern int errno;

/* Globals also used by msg.c */
int fd;
union msg msgp;

void shutdown 	( );
void service 	( );

main (int argc, char * argv [ ] ) {

	int size;
	int to_server;
	int from_server;
	int msgd;


	msgd = msgget ( KEY_MSGQ, IPC_CREAT | 0744 );

	to_server 	= atoi (argv [ 1 ] );
	from_server = atoi (argv [ 2 ] );

	/*** OPEN DATABASE ***/
	fd = open ( "master.dat", O_RDWR );
	if ( fd < 0 ) {
		fprintf ( stderr, "server: Error in opening master.dat...\n" );
		exit ( 2 );
	}

	printf ( "\nSERVER(%d) STARTED SUCCESSFULLY...\n ", getpid() );

	signal ( SIGUSR1, shutdown );
	signal ( SIGUSR2, service );

	/*** RECEIVE AND SERVICE REQUEST ***/
	while ( 1 ) {
		pause ( );
		size = sizeof (msgp) - sizeof (msgp.type);

		if ( msgrcv ( msgd, &msgp, size, to_server, IPC_NOWAIT ) == -1 ) {  
			fprintf ( stderr, "\nSERVER: msgrcv: errno: %d\n", errno );
			exit ( 3 );
		}
		
	//	printf ("SERVER(%d): RECEIVED %d\n",getpid (), msgp.type );

		/*** HANDLING CLIENT REQUEST ***/
		switch ( msgp.message.transaction.type) {								

				case CREATE:		
				printf ("SERVER: CREAT REQUEST RECEIVED: %d\n", msgp.type);
				create ( );
				break;

			case DEPOSIT:	
				printf ("SERVER(%d): DEPOSIT REQUEST RECEIVED: %d\n", 
						getpid (), msgp.type );
				deposit ( );
				break;

			case BALANCE:
				printf ("SERVER: BALANCE REQUEST RECEIVED: %d\n", msgp.type);
				balance ( );
				break;

			case CHANGE:
				printf ("SERVER: CHANGE REQUEST RECEIVED: %d\n", msgp.type);
				change ( );
				break;
		}

	 }
}

void service ( ) { };

void shutdown ( ) {
	printf ( "SHUTING DOWN SERVER(%d)...\n", getpid ( ) );
	close (fd);
	exit (0);
}
