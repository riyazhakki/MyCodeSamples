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

# include "msg.h"

static int msgd;
static int from_server;
static int to_server;

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
//	get_pid		 	( );
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
	send_message ( msgd, &message, size );

	size = sizeof (chan_reply) - sizeof (chan_reply.type);
	receive_message ( msgd, &chan_reply, size, BIG + MASTER_REPLY );

	if ( chan_reply.result == CHAN_FULL){
		printf ("CLIENT: \033[0m CHANNELS BUSY TRY AGAIN...\033[0m\n"); 
		exit ( 1 );
	}
	from_server = chan_reply.from_server;
	to_server	= chan_reply.to_server;
//	printf ("CLIENT: to server :%d\tfrom server :%d\n", to_server,from_server );
}

void trans_request ( char * argv[] ){
	char to_server_str[10];
	char from_server_str [10];

	sprintf ( to_server_str,"%d", to_server );
	sprintf ( from_server_str,"%d", from_server );

	/* argv [1] => [deposit] [withdraw]...*/
	execl ( argv [1], argv [1], argv [2], argv [3],
		to_server_str, from_server_str, NULL); 
}
