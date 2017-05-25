/****server.c****/

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <sys/sem.h>
# include <sys/types.h>

# include "dbase.h"

extern int errno;

//Globals
int fd;
int pid;
struct message *message;

static int shmd;
static int semd;
static union semun { int val; }semun_arg;

void service 	( ); 
void shutdown 	( );
void save_server_pid ( );

void lock_field ( int fd, int ptr,  int size ); 
void unlock_field ( int fd, int ptr,  int size ); 

main (int argc, char * argv [ ] ) {

	int size;
	int to_server;
	int from_server;

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

	shmd = shmget ( (key_t) getuid ( ), 100, IPC_CREAT | 0600 );
	semd = semget ( (key_t) getuid ( ), 1  , IPC_CREAT | 0744 );

	message = ( struct message * ) shmat ( shmd, 0, 0 );

	semun_arg.val = 1;
	semctl ( semd, 0, SETVAL, semun_arg );

	fd = open ( "../dbase/sb.dat", O_RDWR );

	signal ( SIGUSR1, shutdown );
	signal ( SIGUSR2, service );

	printf ( "\nSERVER(%d) STARTED SUCCESSFULLY...\n ", getpid() );

	while ( 1 ) {
		pause ( );

		to_server = message [ MASTER_REQUEST ].type;

		while ( message [ to_server ].status != IDLE );

		switch ( message [ to_server ].transaction.type ) {								
			case CHAN_REQUEST:		
				printf ("CHANNEL REQUEST from %d\n", message[MASTER_REQUEST].type);
				channel ( to_server );
				break;

			case DEPOSIT:
				printf ("DEPOSIT REQUEST from %d\n", message[MASTER_REQUEST].type);
				deposit ( fd, to_server );
				break;

			case WINDUP:
				printf ("WINDUP REQUEST from %d\n", message[MASTER_REQUEST].type);
				windup ( to_server );
				break;
		}
	}
}

void save_server_pid ( int pid ) {
	char filename [20];
	int fd_save_pid;

	sprintf ( filename, "../dbase/sbd_%d", getuid ( ) );
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
	struct shmid_ds *arg;
	printf ( "SHUTING DOWN SERVER\n" );
	shmctl ( shmd, IPC_RMID, arg );
	semctl ( semd, 0, IPC_RMID ); 
	close  ( fd );
	exit   ( 0 );
}

