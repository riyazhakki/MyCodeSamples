/* Windup amount */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/msg.h>
# include <fcntl.h>
# include "dbase.h"
# include "msg.h"

main ( int argc, char *argv [ ] ) {

	int size;
	int msgd;
	int from_server;
	int to_server;

	struct message message;
	struct windup_reply windup_reply;

	msgd = msgget ( (key_t) KEY_MSGQ, 0744 );
	to_server 	= atoi ( argv [ 1 ] );
	from_server = atoi ( argv [ 2 ] );
	from_server += BIG;

	message.type 					= to_server;
	message.transaction.windup.type = WINDUP; 

	size = sizeof ( message.transaction );
	send_message ( msgd, &message, size );

	size = MESSAGE_SIZE(windup_reply);
	receive_message ( msgd, &windup_reply, size, from_server );

	if ( windup_reply.result == SUCCESS ) {
		printf (" TRANSACTION SUCCESSFULL.\n" );
	}	
}
