# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <errno.h>

# include "sb.h"
# include "dbase.h"

void deposit ( int fd , union transaction transaction ){

	int acc_no;
	int amount;
	int pointer;
	int size;
	int fdmreq;
	int fddrep;
	char from_server [ 20 ];
	char to_server [ 20 ];

	struct record rec;
	struct deposit_reply deposit_reply;

	strcpy ( from_server , transaction.deposit.from_server );
	fddrep =  open ( from_server,  	   O_NONBLOCK | O_WRONLY );

	acc_no 	= transaction.deposit.acc_no;
	amount 	= transaction.deposit.amount;

	if ( acc_no > TOTAL_REC) {
		fprintf ( stderr, "SERVER: Invalid account number...!\n" );
		deposit_reply.result = FAIL;
		write ( fddrep, &deposit_reply, sizeof ( deposit_reply ) );
		return;
	}
	pointer = (acc_no - 1) * sizeof (rec) + sizeof (rec.name)
							+ sizeof ( rec.phone ) + 2;
	lock_field ( fd, pointer, sizeof ( rec.balance ) );

	read ( fd, &rec.balance, sizeof ( rec.balance ) );
	printf ("Old Balance: %d\n", rec.balance);
	sleep (5);
	rec.balance += amount;
	printf ("New Balance: %d\n\n", rec.balance);
	lseek ( fd, pointer, SEEK_SET );
	write ( fd, &rec.balance, sizeof (rec.balance) );

 	unlock_field ( fd, pointer, sizeof (rec.balance ) );
	write ( fddrep, &deposit_reply, sizeof ( deposit_reply ) );
}
