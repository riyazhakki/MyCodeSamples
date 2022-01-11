/* Deposit amount */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <string.h>
# include <sys/types.h>
# include <sys/shm.h>
# include <errno.h>

# include "dbase.h"

main ( int argc, char *argv [ ] ) {
	char to_server [20];
	char from_server [20];
	int fdmreq, fddrep;
	int acc_no;
	int amount;
	int pid;
	int red;
	struct deposit deposit;
	struct deposit_reply deposit_reply;

	if ( argc < 3 ) {
		fprintf ( stderr, " <deposit> <acc_no.> <amount> \n" );
		exit (1);
	}
	acc_no 		= atoi ( argv [ 1 ] );
	amount 		= atoi ( argv [ 2 ] );
	strcpy ( to_server,   argv [ 3 ] );
	strcpy ( from_server, argv [ 4 ] );

	if ( amount < 1 ) {
		fprintf ( stderr, "Invalid amount...!\n");
		exit (4);
	}

	fdmreq = open ( "MASTER_REQUEST", O_NONBLOCK | O_WRONLY );
	fddrep = open ( from_server		, O_NONBLOCK | O_RDONLY );
	deposit.type 	= DEPOSIT; 
	deposit.acc_no 	= acc_no;
	deposit.amount 	= amount; 

	strcpy ( deposit.to_server, to_server );
	strcpy ( deposit.from_server, from_server );

	write ( fdmreq, &deposit, sizeof (deposit) );

	get_pid ( &pid );
	red = read ( fddrep, &deposit_reply, sizeof (deposit_reply) );
	while ( ( ( red < 0 ) && ( errno == EAGAIN ) ) || red == 0){
		red = read ( fddrep, &deposit_reply, sizeof (deposit_reply) );
		printf ("Waiting deposit reply\r" );
		fflush ( stdout );
		kill (pid , SIGUSR2 );
	}
	if ( deposit_reply.result == FAIL )
		printf ( "DEPOSIT FAIL...\n" );

	execl ( "windup", "windup", argv [3],  argv [4], NULL ); 
	printf ( "CLIENT:DEPOSIT:windup not exec'ed...\n" );
}
