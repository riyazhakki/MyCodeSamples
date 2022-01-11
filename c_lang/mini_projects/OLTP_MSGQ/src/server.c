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

# include "dbase.h"
# include "msg.h"
# include "sb.h"
# include "sem.h"

extern int errno;

//Globals
int fd;
union msg msgp;
int pid;

static int msgd;
static int semd;
static union semun { int val; }semun_arg;

void save_server_pid ( );
void shutdown 	( );
void service 	( );
void create 	( );
void deposit 	( );
void withdraw	( );
void change 	( );
void balance 	( );

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

	msgd = msgget ( (key_t) KEY_MSGQ, 	IPC_CREAT | 0744 );
	semd = semget ( (key_t) KEY_SEM, 1,	IPC_CREAT | 0744 );

	semun_arg.val = 1;
	semctl ( semd, 0, SETVAL, semun_arg );

	size = MESSAGE_SIZE(msgp); 

	while ( msgrcv ( msgd, &msgp, size, -BIG, IPC_NOWAIT ) != -1 )
		printf ( "FLUSING MESSAGE Q\n" );

	fd = open ( "../dbase/sb.dat", O_RDWR );

	printf ( "\nSERVER(%d) STARTED SUCCESSFULLY...\n ", getpid() );

	signal ( SIGUSR1, shutdown );
	signal ( SIGUSR2, service );

	while ( 1 ) {
		pause ( );

		if ( msgrcv ( msgd, &msgp, size, -BIG, IPC_NOWAIT ) == -1 ) {  
			fprintf ( stderr, "\nSERVER: msgrcv: errno: %d\n", errno );
		}
		
		switch ( msgp.message.transaction.type) {								

			case CHAN_REQUEST:		
			//	printf ("CHANNEL REQUEST from %d\n", msgp.type);
				channel ( );
				break;

			case WINDUP:		
				//printf ("WINDUP REQUEST FROM CLIENT-%d\n",(msgp.type - 1) / 2 );
				windup ( );
				break;

			case CREATE:		
				printf ("CREAT REQUEST CLIENT-%d\n", 
								( msgp.type - 1 ) / 2 );
				create ( );
				break;

			case DEPOSIT:	
				printf ("DEPOSIT REQUEST FROM CLIENT-%d\n", 
								( msgp.type - 1 ) / 2 );
				deposit ( );
				break;

			case BALANCE:
				printf ("BALANCE REQUEST FROM CLIENT-%d\n",
								( msgp.type - 1 ) / 2 );
				balance ( );
				break;

			case CHANGE:
				printf ("CHANGE REQUEST FROM CLIENT-%d\n", 
								( msgp.type - 1 ) / 2 );
			change ( );
				break;
		}

	 }
}

void service ( ) { };

void shutdown ( ) {
	struct msqid_ds *msg_arg;
	printf ( "SHUTING DOWN SERVER\n" );
	msgctl ( msgd, IPC_RMID, msg_arg );
	semctl ( semd, 0, IPC_RMID ); 
	close (fd);
	exit (0);
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

void create ( ) {

}

void deposit ( ) {
	
	int acc_no;
	int amount;
	int pointer;
	int size;

	struct record rec;
	static struct deposit_reply deposit_reply;

	msgd	= msgget ( KEY_MSGQ, 0744 );
	acc_no 	= msgp.message.transaction.deposit.acc_no;
	amount 	= msgp.message.transaction.deposit.amount;

	deposit_reply.type = REPLY;
	size = MESSAGE_SIZE(deposit_reply);

	if ( acc_no > TOTAL_REC) {
		fprintf ( stderr, "SERVER: Invalid account number...!\n" );
		deposit_reply.result = FAIL;
		send_message ( msgd, &deposit_reply, size );
		return;
	}

	pointer = (acc_no - 1) * sizeof (rec) 
					+ sizeof (rec.name)+ sizeof ( rec.phone )+2;
	if ( lseek ( fd, pointer, SEEK_SET ) < 0 ){
		fprintf ( stderr, "Error in seeking file...!\n" );
		return;
	}

	/* LOCKING */
	while ( lockf ( fd, F_TLOCK, sizeof ( rec.balance ) ) == -1 ){
		deposit_reply.result = WAIT ;
	//	send_message ( msgd, &deposit_reply, size );
		sleep (2);
	}

	/********* RMW Cycle ***********/	

	/* Read */
	read ( fd, &rec.balance, sizeof ( rec.balance ) );
	printf ("Old Balance: %d\n", rec.balance);

	sleep (5);
	/* Modify */
	rec.balance += amount;
	printf ("New Balance: %d\n\n", rec.balance);

	/* Write */
	lseek ( fd, pointer, SEEK_SET );
	write ( fd, &rec.balance, sizeof (rec.balance) );

	/* UNLOCKING */
	lseek ( fd, pointer, SEEK_SET );
	lockf ( fd, F_ULOCK, sizeof (rec.balance) );
	
	deposit_reply.result = SUCCESS;
	send_message ( msgd, &deposit_reply, size );
}

void withdraw ( ) {

}

void balance ( ) {

}

void change ( ) {

}
