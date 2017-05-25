/****server.c****/

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

extern char chan_status [ ];
extern int nmax;
extern int errno;

union msg msgp;
int fd;

static int msgd;
static struct msqid_ds *arg;

static int semd;

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

	printf ( "SERVER(%d) STARTED SUCCESSFULLY...\n ", getpid() );

	signal ( SIGUSR1, shutdown );
	signal ( SIGUSR2, service );
	signal ( SIGCHLD, SIG_IGN );

	/*** RECEIVE AND SERVICE REQUEST ***/
	while ( 1 ) {
		pause ( );
		size = sizeof (msgp) - sizeof (msgp.type);
		if ( msgrcv ( msgd, &msgp, size, -20, IPC_NOWAIT ) == -1 ) {  
			fprintf ( stderr, "\nSERVER: msgrcv: errno: %d\n", errno );
			exit ( 3 );
		}
		
		printf ("SERVER(%d): RECEIVED %d\n",getpid (), msgp.type );

		/*** HANDLING CLIENT REQUEST ***/
		switch ( msgp.message.transaction.type) {								
			case CHAN_REQUEST:
				printf ("SERVER(%d): CHAN_REQUEST RECEIVED: %d\n", 
					getpid (), msgp.type );
				channel ( );
				break;

			case CREATE:		
				printf ("SERVER: CREAT REQUEST RECEIVED: %d\n", msgp.type);
				create ( );
				break;

			case DEPOSIT:	
				printf ("SERVER(%d): DEPOSIT REQUEST RECEIVED: %d\n", 
						getpid (), msgp.type );
				deposit ( );
				break;

			case BALANCE:
				printf ("SERVER: BALANCE REQUEST RECEIVED: %d\n", msgp.type);
				balance ( );
				break;

			case CHANGE:
				printf ("SERVER: CHANGE REQUEST RECEIVED: %d\n", msgp.type);
				change ( );
				break;

			case WINDUP:
				printf ("SERVER (%d) :WINDUP REQUEST RECEIVED: %d\n",
						getpid (), msgp.type);
				windup ( );
				break;
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
