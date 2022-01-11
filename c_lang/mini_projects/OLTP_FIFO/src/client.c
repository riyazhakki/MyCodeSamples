/*** client.c ***/

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include "dbase.h"

static char from_server [20];
static char to_server [20];

void chan_request 	( void );
void trans_request	( char * argv [ ] );

main ( int argc, char * argv [] ) {

	if ( argc < 3 ){
		fprintf ( stderr, "<client> <transaction_name> <param1> ...\n" );
		exit ( 1 );
	}
	if ( open ( "MASTER_REQUEST", O_WRONLY | 0600) == -1 ){
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
	int fdmreq, fdmrep;
	int red;
	struct chan_request chan_request;
	struct chan_reply chan_reply;

	fdmreq = open ( "MASTER_REQUEST", O_NONBLOCK | O_WRONLY | 0600 );
	fdmrep = open ( "MASTER_REPLY",   O_NONBLOCK | O_RDONLY | 0600 );

	chan_request.type = CHAN_REQUEST;
	write ( fdmreq, &chan_request, sizeof (chan_request) );

	get_pid ( &pid );
	red = read (fdmrep, &chan_reply , sizeof (chan_reply)); 
	while ( ( red < 0 && errno == EAGAIN ) || red == 0){
		red = read ( fdmrep, &chan_reply , sizeof (chan_reply) ); 
		printf ("\033[0m PLEASE WAIT...\033[0m\r");	
		fflush (stdout);
		kill ( pid, SIGUSR2 );
	}

	if ( chan_reply.result == CHAN_FULL ) {
		printf ("CLIENT: \033[0m CHANNELS BUSY TRY AGAIN...\033[0m\n"); 
		exit ( 1 );
	}
	strcpy ( to_server, chan_reply.to_server );
	strcpy ( from_server, chan_reply.from_server );
	printf ("CLIENT: to server :%s\tfrom server :%s\n", to_server,from_server );

	close ( fdmreq );
	close ( fdmrep );
}

void trans_request ( char * argv[] ){

	/* argv [1] => [deposit] [withdraw]...*/

	execl ( argv [1], argv [1], argv [2], argv [3],
		to_server, from_server, NULL); 
}

