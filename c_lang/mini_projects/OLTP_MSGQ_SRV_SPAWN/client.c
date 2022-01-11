/*** client.c ***/

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/ipc.h>
# include <sys/types.h>
# include <sys/msg.h>
# include <signal.h>
# include <unistd.h>
# include <errno.h>
# include "dbase.h"

extern int errno;
static int msgd;
static int pid;
static int from_server;
static int to_server;

void get_server_pid ( void );
void chan_request 	( void );
void trans_request	( char * argv [ ] );

main ( int argc, char * argv [] ) {

	if ( argc < 3 ){
		fprintf ( stderr, "<client> <transaction_name> <param1> ...\n" );
		exit ( 1 );
	}
	if ( (msgd = msgget ( (key_t) KEY_MSGQ, 0744 )) == -1 ){
		fprintf ( stderr, "NO SERVER TO COMMUNICATE...\n" );
		exit ( 1 );
	}			
	get_server_pid 	( );
	chan_request 	( );
	trans_request	( argv );
}	

void chan_request ( ) {
	int size;
	char byte;
	struct message message;
	struct chan_reply chan_reply;

	message.type = MASTER_REQUEST; 
	message.transaction.chan_request.type = CHAN_REQUEST;

	size =  sizeof( message ) - sizeof ( message.type );
	if ( msgsnd ( msgd, &message, size , IPC_NOWAIT ) != -1 )
		kill ( pid, SIGUSR2 );
	//else
	//	printf ("CLIENT: CHAN_REQUEST SENT from %d\n", message.type  );

	size = sizeof (chan_reply) - sizeof (chan_reply.type);
	while ( msgrcv ( msgd, &chan_reply, size, BIG + MASTER_REPLY, IPC_NOWAIT ) == -1 ) {
		printf ( "CLIENT: waiting for channel_reply \r");
		sleep (1);
	}
	putchar ('\n');

	if ( chan_reply.result == CHAN_FULL){
		printf ("CLIENT: \033[0m ALL CHANNELS ARE BUSY TRY AGAIN...\n");
		printf ("\033[0m");
		exit ( 1 );
	}

	from_server = chan_reply.from_server;
	to_server	= chan_reply.to_server;
	pid			= chan_reply.server_pid;

	printf ("CLIENT: to server :%d\tfrom server :%d\n", to_server,from_server );
	//printf ("CLIENT: server_pid = %d\n", pid );
}

void trans_request ( char * argv[] ){
	char to_server_str[10];
	char from_server_str [10];
	char pid_str [10];

	sprintf ( to_server_str,"%d", to_server );
	sprintf ( from_server_str,"%d", from_server );
	sprintf ( pid_str,"%d", pid);

	/* argv [1] => deposit or withdraw or change or blance */

	execl ( argv [1], argv [1], argv [2], argv [3],
		to_server_str, from_server_str, pid_str, NULL); 
	printf ("CLIENT: trnas_request: execl: errno: %d\n", errno );
}

void get_server_pid ( ) {
	int fd;
	char filename [20];

	sprintf ( filename, "sbd_%d", getuid ( ) );
	fd = open ( filename,  O_RDWR );
	if ( fd < 0 ) {
		fprintf ( stderr, "Error in file opening...\n" );
		exit ( 1 );
	}
	read ( fd, &pid, sizeof (pid) ); // for sending signal to server
	close (fd);
}
