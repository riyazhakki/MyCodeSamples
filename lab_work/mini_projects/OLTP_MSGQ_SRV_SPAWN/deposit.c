/* Deposit amount */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/msg.h>

# include "dbase.h"

main ( int argc, char *argv [ ] ) {
	int fd;
	int acc_no;
	int amount;
	int size;
	int msgd;
	int pid;
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
	pid 		= atoi ( argv [ 5 ] );

	//printf ("CLIENT:DEPOSIT:server_pid:%d\n", pid );
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

	if ( msgsnd ( msgd, &message, size, IPC_NOWAIT ) != -1 ){
		kill ( pid, SIGUSR2 );
	//	printf ( "CLIENT:DEPOSIT: REQUEST SENT SUCCESSFULY from :%d\n", 
						//message.type );
	}
	else
		printf ( "DEPOSIT: deposit request not sent...\n");

	size = sizeof ( deposit_reply ) - ( deposit_reply.type );
	while ( msgrcv ( msgd, &deposit_reply, size, from_server, IPC_NOWAIT ) == -1 ) {
		printf ( "CLIENT: waiting for deposit reply from %d...\r",
							from_server );
		sleep ( 1 );
	}
	putchar ( '\n' );

	while ( deposit_reply.result == WAIT ) {
		printf ( "\033[5mPLEASE WAIT...\033[0m\r" );
		fflush ( stdout );
		msgrcv ( msgd, &deposit_reply, size, from_server, IPC_NOWAIT ); 
	}

	if ( deposit_reply.result == SUCCESS ) { 
		printf ("\033[0mTRANSACTION SUCCESSFULL...\033[0m\n");
		execl ( "windup", "windup", argv [3], argv [4], argv [5], NULL ); 
		printf ( "windup not execed...\n" );
	}
	else if ( deposit_reply.result = FAIL ){
		printf ( "CLIENT:DEPOSIT: TRANSACTION FAIL...\n" );
		execl ( "windup", "windup", argv [3],  argv [4], 	argv [5], NULL ); 
								/*  to_server, from_server, pid 	*/
		printf ( "windup not exec'ed...\n" );
	}
}
