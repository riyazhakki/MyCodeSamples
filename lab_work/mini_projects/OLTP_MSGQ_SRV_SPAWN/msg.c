# include <sys/types.h>
# include <sys/msg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include "dbase.h"
# include "sb.h"

extern errno;
extern union msg msgp;
extern int fd;
static int msgd;

void create ( ) {

}

void deposit ( ) {
	
	int acc_no;
	int amount;
	int pointer;
	int size;

	struct record rec;
	static struct deposit_reply deposit_reply;

	msgd = msgget ( KEY_MSGQ, 0744 );
	acc_no = msgp.message.transaction.deposit.acc_no;
	amount = msgp.message.transaction.deposit.amount;

	deposit_reply.type = BIG + msgp.message.type + 1;
	size = sizeof ( deposit_reply ) - sizeof ( deposit_reply.type );

	if ( acc_no > TOTAL_REC) {
		fprintf ( stderr, "SERVER: Invalid account number...!\n" );
		deposit_reply.result = FAIL;
		msgsnd ( msgd, &deposit_reply, size, IPC_NOWAIT );
		return;
	}

	if ( amount < 1 ) {
		fprintf ( stderr, "SERVER: Invalid amount...!\n");
		deposit_reply.result = FAIL;
		msgsnd ( msgd, &deposit_reply, size, IPC_NOWAIT );
		return;
	}

	pointer = (acc_no - 1) * sizeof (rec) 
					+ sizeof (rec.name)+ sizeof ( rec.phone )+2;
	if ( lseek ( fd, pointer, SEEK_SET ) < 0 ){
		fprintf ( stderr, "Error in seeking file...!\n" );
		exit (6);	
	}

	/* LOCKING */
	while ( lockf ( fd, F_TLOCK, sizeof ( rec.balance ) ) == -1 ){
		deposit_reply.result = WAIT ;
		msgsnd ( msgd, &deposit_reply, size, IPC_NOWAIT );
		sleep (2);
	}
	putchar ('\n');

	/********* RMW Cycle ***********/	

	/* Read */
	read ( fd, &rec.balance, sizeof ( rec.balance ) );
	printf ("SERVER:(%d) Old Balance: %d\n", getpid (), rec.balance);

	sleep (5);
	/* Modify */
	rec.balance += amount;
	printf ("SERVER:(%d): New Balance: %d\n", getpid (), rec.balance);

	/* Write */
	lseek ( fd, pointer, SEEK_SET );
	write ( fd, &rec.balance, sizeof (rec.balance) );

	/* UNLOCKING */
	lseek ( fd, pointer, SEEK_SET );
	lockf ( fd, F_ULOCK, sizeof (rec.balance) );
	
	size = sizeof (deposit_reply ) - sizeof ( deposit_reply.type );
	deposit_reply.type 	 = BIG + msgp.message.type + 1;
	deposit_reply.result = SUCCESS;
	if (msgsnd ( msgd, &deposit_reply, size, IPC_NOWAIT ) != -1 )
		printf ( "SERVER(%d):DEPOSIT: REPLY SENT SUCCESSFULLY...\n", getpid() );

//	exit ( 0 );  //child server
}

void withdraw ( ) {

}

void balance ( ) {

}

void change ( ) {

}
