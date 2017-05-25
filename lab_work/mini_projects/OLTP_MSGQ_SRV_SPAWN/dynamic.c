/*** dynamic.c ***/

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <sys/ipc.h>
# include <sys/msg.h>
# include <sys/sem.h>
# include <sys/types.h>

# include "dynamic.h"
# include "dbase.h"
# include "sb.h"
# include "msg.h"

extern int errno;

char chan_status [ CMAX ];
int nmax = CMAX;

union msg msgp;
int fd;

static int msgd;
static int semd;

static struct msqid_ds *arg;

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};


void save_server_pid ( );
void shutdown 		 ( );
void service 	 	 ( );

main ( ) {

	int pid;
	int size;

	union semun sem_arg;
	struct sembuf sop;

	/** MASTER CHANNEL PAIR **/
	chan_status [ 0 ] = 1;
	chan_status [ 1 ] = 1;
	chan_status [ 2 ] = 1;

	switch ( pid = fork ( ) ) {

		case -1 : fprintf ( stderr, "Child not created...\n" );
					exit ( 1 );
		case  0 : break;

		default : save_server_pid ( pid );
					exit ( 0 );
	}

	setpgrp ( );
	close ( 0 );
//	close ( 1 );
//	close ( 2 );

	/*** CREATE MESSAGE QUEUE & SEMAPHORE  ***/
	msgd = msgget ( (key_t) KEY_MSGQ, 	IPC_CREAT | 0744 );
	semd = semget ( (key_t) KEY_SEM, 1, IPC_CREAT | 0744 );

	sem_arg.val = 1;
	semctl ( semd, 0 , SETVAL, sem_arg );

	/*** FLUSING PREVIOUS CONTENTS  ***/
	size = sizeof (msgp) - sizeof (msgp.type);
	while ( msgrcv ( msgd, &msgp, size, -20, IPC_NOWAIT ) != -1 ){
		printf ( "FLUSING MESSAGE Q\n" );
	}

	/*** OPEN DATABASE ***/
	fd = open ( "master.dat", O_RDWR );
	if ( fd < 0 ) {
		fprintf ( stderr, "server: Error in opening master.dat...\n" );
		exit ( 2 );
	}

	printf ( "\nD_SERVER(%d) STARTED SUCCESSFULLY...\n ", getpid() );

	signal ( SIGUSR1, shutdown );
	signal ( SIGUSR2, service );
	signal ( SIGCHLD, SIG_IGN );

	/*** RECEIVE AND SERVICE REQUEST ***/
	while ( 1 ) {
		pause ( );
		size = sizeof (msgp) - sizeof (msgp.type);
		if ( msgrcv ( msgd, &msgp, size, MASTER_REQUEST, IPC_NOWAIT ) == -1 ) {  
			fprintf ( stderr, "\nD_SERVER(%d): msgrcv: errno: %d\n",getpid(), errno );
			exit ( 3 );
		}
		
	//	printf ("D_SERVER(%d): RECEIVED %d\n",getpid (), msgp.type );

		if ( msgp.message.transaction.type == CHAN_REQUEST ){
			printf ( "D_SERVER (%d) RECEIVED CHAN REQUEST\n",getpid() );
			channel ( );  // allocate channel and fork child server
		}
		else if ( msgp.message.transaction.type == WINDUP ){
			printf ( "D_SERVER (%d) RECEIVED WINDUP REQUEST\n",getpid() );
			windup ( );
		}
	 }
}

void save_server_pid ( int pid ) {
	char filename [20];
	int fd_save_pid;

	sprintf ( filename, "sbd_%d", getuid ( ) );
	fd_save_pid = open ( filename, O_CREAT | O_TRUNC | O_WRONLY, 0744 );
	if ( fd_save_pid < 0 ) {
		fprintf ( stderr, "Error in file opening...\n" );
		exit ( 1 );
	}
	write ( fd_save_pid, &pid, sizeof (pid) );
	close ( fd_save_pid );
}

void service ( ) { };

void shutdown ( ) {
	msgctl ( msgd, IPC_RMID, arg );
	semctl ( semd, 0, IPC_RMID );
	printf ( "SHUTING DOWN SERVER...\n" );
	close (fd);
	exit (0);
}

void channel ( ) {
	int size;
	int n = 1;
	int i;
	int pid;
	int semd;

	char to_server_str [10];
	char from_server_str [10];

	struct chan_reply chan_reply;
	struct sembuf sop;

	chan_reply.type	= BIG + MASTER_REPLY;
	size = sizeof (chan_reply) - sizeof (chan_reply.type);

	semd = semget ( KEY_SEM, 1, IPC_CREAT );
	msgd = msgget ( KEY_MSGQ, IPC_CREAT | 0744 );

	/* lookin for free channels */
	for ( n = 2; ((chan_status [ 2 * n ] != 0) && (n < MAX_CH_PAIR + 1)); n++ );

	if ( n > MAX_CH_PAIR ){
		chan_reply.result 	= CHAN_FULL;
		msgsnd ( msgd, &chan_reply, size,IPC_NOWAIT );
		return;
	}

	sprintf ( to_server_str, "%d", TO_SERVER );
	sprintf ( from_server_str, "%d", FROM_SERVER );

	switch ( pid = fork ( ) ) {
		case -1 : 
					printf ( "SERVER : DYNAMIC : CAN'T FORKED...\n" );
				 	break;	
		case  0 :
					execl ( "server", "server", to_server_str, from_server_str,"NULL" ); 
					fprintf ( stderr, "Child server not execed...\n" );
		default : 	
					break;;
	}

	chan_reply.result 			= SUCCESS;
	chan_reply.to_server		= TO_SERVER;
	chan_reply.from_server 		= FROM_SERVER;
	chan_status [ TO_SERVER ] 	= BUSY;
	chan_status [ FROM_SERVER ] = BUSY;
	chan_reply.server_pid 		= pid;

	msgsnd ( msgd, &chan_reply, size, IPC_NOWAIT ); 
}

void windup ( ) {

int size;
struct windup_reply windup_reply;

msgd = msgget ( KEY_MSGQ, IPC_CREAT | 0744 );
chan_status [ msgp.message.transaction.windup.to_server 	] 	= IDLE;
chan_status [ msgp.message.transaction.windup.from_server 	] 	= IDLE;
windup_reply.type 	= BIG + MASTER_REPLY;
windup_reply.result = SUCCESS;
size = sizeof ( windup_reply ) - sizeof ( windup_reply.type );
if (! msgsnd ( msgd, &windup_reply, size, IPC_NOWAIT ) )
	printf ("SERVER (%d): WINDUP: REPLY SENT SUCCESSFULLY...\n", getpid ()  );
}
