/*** dynamic.c ***/

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/ipc.h>
# include <sys/shm.h>

# include "dbase.h"

# define MAX_CH_PAIR 	3	

static char chan_status [ 2 * MAX_CH_PAIR + 1 ];

void channel 	( int to_server );
void windup 	( int to_server );

extern int errno;
extern int fd;  // access from server.c

void channel ( int to_server ) {

	int size;
	int n = 1;
	int i;
	int pid;
	int shmd;


	struct message *message;

	shmd = shmget ( (key_t) getuid ( ), 100, 0600 );
	message = ( struct message * ) shmat ( shmd, 0, 0 );

	chan_status [ 0 ] = 1;
	chan_status [ 1 ] = 1;
	chan_status [ 2 ] = 1;

	sem_lock ( );
	//sleep ( 3 );
	/* lookin for free channels */
	for ( n = 1; ((chan_status [ 2 * n ] != 0) && (n < MAX_CH_PAIR + 1)); n++ );

	if ( n > MAX_CH_PAIR ){
		message [ MASTER_REPLY ].transaction.chan_reply.result 	= CHAN_FULL;
		message [ to_server ].status 							= WRITTEN;
		sem_unlock ( );
		return;
	}

	message [ MASTER_REPLY ].transaction.chan_reply.result 		= SUCCESS;
	message [ MASTER_REPLY ].transaction.chan_reply.to_server	= 2 * n - 1;
	message [ MASTER_REPLY ].transaction.chan_reply.from_server	= 2 * n;
	message [ to_server ].status 								= WRITTEN;

	sem_unlock ( );

	chan_status [ 2 * n - 1] = BUSY;
	chan_status [ 2 * n    ] = BUSY;
}

void windup ( int to_server ) {
	int size;
	int shmd;
	int from_server = to_server + 1;
	struct message *message;

	shmd = shmget ( (key_t) getuid (), 100, 0600 );
	message = (struct message * ) shmat ( shmd, 0, 0 );

	chan_status [ to_server   ] = IDLE;
	chan_status [ from_server ] = IDLE;

	message [ from_server ].transaction.windup_reply.result = SUCCESS;
	message [ to_server ].status = WRITTEN;	
}
