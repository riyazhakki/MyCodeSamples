/* Windup amount */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/msg.h>
# include <fcntl.h>
# include "dbase.h"

void get_server_d_pid ( );

static int d_pid;

main ( int argc, char *argv [ ] ) {

	int size;
	int msgd;
	int from_server;
	int to_server;
	int s_pid;

	struct message message;
	struct windup_reply windup_reply;

	msgd = msgget ( (key_t) KEY_MSGQ, 0744 );
	to_server 	= atoi ( argv [ 1 ] );
	from_server = atoi ( argv [ 2 ] );
	s_pid		= atoi ( argv [ 3 ] );

	get_server_d_pid ( );

	message.type 							= MASTER_REQUEST;
	message.transaction.windup.type 		= WINDUP; 
	message.transaction.windup.to_server 	= to_server;
	message.transaction.windup.from_server 	= from_server;

	size = sizeof ( message.transaction );
	msgsnd ( msgd, &message, size, IPC_NOWAIT );
	kill ( d_pid, SIGUSR2 );

	kill ( s_pid, SIGUSR1 );  //shutdown server

	//printf ("CLIENT:WINDUP: request sent to server(%d)\n", d_pid );

	size = 	sizeof ( windup_reply ) - sizeof ( windup_reply.type );
	while ( msgrcv ( msgd, &windup_reply, size, BIG + MASTER_REPLY, IPC_NOWAIT ) == -1 ) {
		printf ( "CLIENT:WINDUP:WAITING FOR REPLY...\r" );
		fflush (stdout);
		sleep ( 1 );
	}
	putchar ('\n');
	if ( windup_reply.result == SUCCESS ) 
		printf ( "WINDUP COMPLETED SUCCESSFULLY...\n");
}

void get_server_d_pid ( ) {
	int fd;
	char filename [20];

	sprintf ( filename, "sbd_%d", getuid ( ) );
	fd = open ( filename,  O_RDWR );
	if ( fd < 0 ) {
		fprintf ( stderr, "Error in file opening...\n" );
		exit ( 1 );
	}
	read ( fd, &d_pid, sizeof (d_pid) ); // for sending signal to server
	close (fd);
}
