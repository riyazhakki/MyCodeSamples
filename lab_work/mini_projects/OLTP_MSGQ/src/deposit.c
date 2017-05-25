/* Deposit amount */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/msg.h>

# include "dbase.h"
# include "msg.h"

main ( int argc, char *argv [ ] ) {
	int fd;
	int acc_no;
	int amount;
	int size;
	int msgd;
	int from_server;
	int to_server;

	struct message message;
	struct deposit_reply deposit_reply;

	msgd = msgget ( (key_t) KEY_MSGQ, 0744 );

	if ( argc < 3 ) {
		fprintf ( stderr, " <deposit> <acc_no.> <amount> \n" );
		exit (1);
	}

	acc_no 		= atoi ( argv [ 1 ] );
	amount 		= atoi ( argv [ 2 ] );
	to_server 	= atoi ( argv [ 3 ] );
	from_server = atoi ( argv [ 4 ] );

	from_server += BIG;

	if ( amount < 1 ) {
		fprintf ( stderr, "Invalid amount...!\n");
		exit (4);
	}

	message.type 						= to_server;
	message.transaction.deposit.type 	= DEPOSIT; 
	message.transaction.deposit.acc_no 	= acc_no;
	message.transaction.deposit.amount 	= amount; 

	size = sizeof ( message.transaction );
	send_message ( msgd, &message, size );

	size = MESSAGE_SIZE(deposit_reply);
	receive_message ( msgd, &deposit_reply, size, from_server );

	if ( deposit_reply.result == SUCCESS )  {
	//	printf ("\033[0mDEPOSIT SUCCESSFULL...\033[0m\n");
	}
	else if ( deposit_reply.result == FAIL )
		printf ( "DEPOSIT: TRANSACTION FAIL...\n" );

	execl ( "windup", "windup", argv [3],  argv [4], NULL ); 
								/*  to_server, from_server */
	printf ( "CLIENT:DEPOSIT:windup not exec'ed...\n" );
}
