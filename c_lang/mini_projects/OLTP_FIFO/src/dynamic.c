/*** dynamic.c ***/

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <string.h>

# include "dbase.h"

# define MAX_CH_PAIR 	3	

static char chan_status [ 2 * MAX_CH_PAIR + 1 ];

void channel 	( );
void windup 	( );

extern int errno;
extern int fd;  // access from server.c

void channel ( ) {

	int size;
	int n = 1;
	int i;
	int pid;
	int fdm;
	char from_server [ 20 ];
	char to_server 	 [ 20 ];
	struct chan_reply chan_reply;

	fdm = open ( "MASTER_REPLY", O_NONBLOCK | O_WRONLY );

	chan_status [ 0 ] = 1;
	chan_status [ 1 ] = 1;
	chan_status [ 2 ] = 1;

	sem_lock ( );
	printf ("semlock\n");
	sleep ( 3 );
	/* lookin for free channels */
	for ( n = 1; ((chan_status [ 2 * n ] != 0) && (n < MAX_CH_PAIR + 1)); n++ );

	if ( n > MAX_CH_PAIR ){
		chan_reply.result 	= CHAN_FULL;
		write ( fdm, &chan_reply, sizeof( chan_reply ) ); 
		sem_unlock ( );
	//	printf ("semunlock\n");
		return;
	}

	sprintf ( from_server, 	"FIFO%d", 2 * n 	);
	sprintf ( to_server, 	"FIFO%d", 2 * n - 1 );

	mknod ( from_server, S_IFIFO | 0600, 0);
	mknod ( to_server, S_IFIFO | 0600, 0);

	chan_reply.result 		= SUCCESS;
	strcpy ( chan_reply.to_server, to_server );
	strcpy ( chan_reply.from_server, from_server );

	write ( fdm, &chan_reply, sizeof( chan_reply ) ); 
	sem_unlock ( );
	printf ("semunlock\n");

	chan_status [ 2 * n - 1] = BUSY;
	chan_status [ 2 * n    ] = BUSY;
}
void windup ( union transaction transaction ) {
	int size;
	int shmd;
	int to_server;
	int from_server;
	int fdwrep;
	struct windup_reply windup_reply;

	to_server 	= atoi ( transaction.windup.to_server 	+ 4 );
	from_server = atoi ( transaction.windup.from_server + 4 );

	printf ("from_server:%s\n", transaction.windup.from_server );

	fdwrep = open ( transaction.windup.from_server, O_NONBLOCK | O_WRONLY );
	chan_status [ to_server   ] = IDLE;
	chan_status [ from_server ] = IDLE;

	windup_reply.result = SUCCESS;

	remove ( transaction.windup.to_server );
	remove ( transaction.windup.from_server );

	printf ("Written: %d\n", write ( fdwrep, &windup_reply, sizeof ( windup_reply ) ));
}
