/*** client.c ***/

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/ipc.h>
# include <sys/types.h>
# include <sys/shm.h>
# include <signal.h>
# include <unistd.h>
# include "dbase.h"

static int shmd;
static int from_server;
static int to_server;

void chan_request 	( void );
void trans_request	( char * argv [ ] );

main ( int argc, char * argv [] ) {

	if ( argc < 3 ){
		fprintf ( stderr, "<client> <transaction_name> <param1> ...\n" );
		exit ( 1 );
	}
	if ( (shmd = shmget ( (key_t) getuid ( ), 100, 0600 )) == -1 ){
		fprintf ( stderr, "NO SERVER TO COMMUNICATE...\n" );
		exit ( 1 );
	}			
	chan_request 	( );
	trans_request	( argv );
}	

void chan_request ( ) {
	int size;
	char byte;
	int pid;
	struct message *message;

	message = ( struct message * ) shmat ( shmd, 0, 0 );

	if ( message < 0 ) 
		printf ( "error in shmat...\n" );

	message [ MASTER_REQUEST ].type   = MASTER_REQUEST;
	message [ MASTER_REQUEST ].status = IDLE;
	message [ MASTER_REQUEST ].transaction.type = CHAN_REQUEST;	

	get_pid ( &pid );
	while ( message [ MASTER_REQUEST ].status != WRITTEN ){
		printf ("\033[0m PLEASE WAIT...\033[0m\r");	
		fflush (stdout);
		kill ( pid, SIGUSR2 );
	};
	message [ MASTER_REQUEST ].status = IDLE;

	if ( message [ MASTER_REPLY ].transaction.chan_reply.result == CHAN_FULL ) {
		printf ("CLIENT: \033[0m CHANNELS BUSY TRY AGAIN...\033[0m\n"); 
		exit ( 1 );
	}
	to_server   =  message [ MASTER_REPLY ].transaction.chan_reply.to_server;
	from_server =  message [ MASTER_REPLY ].transaction.chan_reply.from_server;
	printf ("CLIENT: to server :%d\tfrom server :%d\n", to_server,from_server );
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

