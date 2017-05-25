/* Deposit amount */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/shm.h>

# include "dbase.h"

main ( int argc, char *argv [ ] ) {
	int fd;
	int acc_no;
	int amount;
	int size;
	int shmd;
	int from_server;
	int to_server;
	int pid;

	struct message *message;

	shmd 	= shmget ( (key_t) getuid ( ), 100, 0600 );
	message = ( struct message * ) shmat  ( shmd, 0  , 0 	 );

	if ( argc < 3 ) {
		fprintf ( stderr, " <deposit> <acc_no.> <amount> \n" );
		exit (1);
	}

	acc_no 		= atoi ( argv [ 1 ] );
	amount 		= atoi ( argv [ 2 ] );
	to_server 	= atoi ( argv [ 3 ] );
	from_server = atoi ( argv [ 4 ] );

	if ( amount < 1 ) {
		fprintf ( stderr, "Invalid amount...!\n");
		exit (4);
	}
	message [ MASTER_REQUEST ].type 					= to_server;
	message [ to_server ].transaction.deposit.type 	    = DEPOSIT; 
	message [ to_server ].transaction.deposit.acc_no 	= acc_no;
	message [ to_server ].transaction.deposit.amount 	= amount; 
	message [ to_server ].status = IDLE;

	get_pid ( &pid );
	while ( message [to_server].status != WRITTEN ){
		message [to_server].status = IDLE;
		printf ("Waiting deposit reply\r" );
		fflush ( stdout );
		kill (pid , SIGUSR2 );
	}
	message [ to_server ].status = IDLE;

	if ( message [from_server].transaction.deposit_reply.result == FAIL )
		printf ( "DEPOSIT FAIL...\n" );

	execl ( "windup", "windup", argv [3],  argv [4], NULL ); 
								/*  to_server, from_server */
	printf ( "CLIENT:DEPOSIT:windup not exec'ed...\n" );
}
