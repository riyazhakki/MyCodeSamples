/*** dynamic.c ***/

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <sys/ipc.h>
# include <sys/msg.h>
# include <sys/types.h>

# include "dbase.h"
# include "sb.h"
# include "msg.h"
# include "sem.h"

# define MAX_CH_PAIR 	3	

static char chan_status [ 2 * MAX_CH_PAIR + 1 ];

void channel 	( void );
void windup 	( void );

extern int errno;
extern union msg msgp;
extern int fd;

static int msgd;

void channel ( ) {
	int size;
	int n = 1;
	int i;
	int pid;

	struct chan_reply chan_reply;

	/** MASTER CHANNEL PAIR **/
	chan_status [ 0 ] = 1;
	chan_status [ 1 ] = 1;
	chan_status [ 2 ] = 1;

	chan_reply.type	= REPLY;
	size = MESSAGE_SIZE(chan_reply);

	msgd = msgget ( (key_t)KEY_MSGQ, IPC_CREAT | 0744 );

	sem_lock ( );
	sleep ( 3 );
	/* lookin for free channels */
	for ( n = 1; ((chan_status [ 2 * n ] != 0) && (n < MAX_CH_PAIR + 1)); n++ );

	if ( n > MAX_CH_PAIR ){
		chan_reply.result 	= CHAN_FULL;
		send_message ( msgd, &chan_reply, size );
		sem_unlock ( );
		return;
	}

	chan_reply.result 			= SUCCESS;
	chan_reply.to_server		= 2 * n - 1;
	chan_reply.from_server 		= 2 * n;
	send_message ( msgd, &chan_reply, size );
	sem_unlock ( );

	chan_status [ 2 * n - 1] = BUSY;
	chan_status [ 2 * n    ] = BUSY;
}

void windup ( ) {

	int size;
	struct windup_reply windup_reply;

	msgd = msgget ( KEY_MSGQ, IPC_CREAT | 0744 );
	chan_status [ msgp.type     ] = IDLE;
	chan_status [ msgp.type + 1 ] = IDLE;

	windup_reply.type 	= REPLY;
	windup_reply.result = SUCCESS;
	
	size = MESSAGE_SIZE(windup_reply);
	send_message ( msgd, &windup_reply, size );
}
