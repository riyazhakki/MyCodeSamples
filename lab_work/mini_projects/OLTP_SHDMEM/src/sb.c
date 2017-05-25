# include <stdio.h>
# include <fcntl.h>
# include <sys/ipc.h>
# include <sys/shm.h>

# include "sb.h"
# include "dbase.h"

static struct message *message;
static int shmd;

void deposit ( int fd, int to_server ){
	int acc_no;
	int amount;
	int pointer;
	int size;
	int from_server;
	struct record rec;

	from_server = to_server + 1;
	shmd    = shmget ( (key_t) getuid(), 100, 0600 );
	message = shmat ( shmd, 0, 0 );
	acc_no 	= message [ to_server ].transaction.deposit.acc_no;
	amount 	= message [ to_server ].transaction.deposit.amount;

	if ( acc_no > TOTAL_REC) {
		fprintf ( stderr, "SERVER: Invalid account number...!\n" );
		message [ from_server ].transaction.deposit_reply.result = FAIL;
		message [ to_server ].status = WRITTEN;
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
	message [ from_server ].transaction.deposit_reply.result = SUCCESS;
	message [ to_server ].status = WRITTEN;
}
