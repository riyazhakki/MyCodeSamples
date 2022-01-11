/* Withdrawal amount */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/sem.h>

# include "sb.h"

main ( int argc, char *argv [ ] ) {
	char chk_balnce [20];
	int fd;
	int acc_no;
	int amount;
	int pointer;

	int semd ;
	struct sembuf sop;
	struct record rec;

	if ( argc < 3 ) {
		fprintf ( stderr, " <deposit> <acc_no.> <amount> \n" );
		exit (1);
	}

	fd = open ( "master.dat", O_RDWR );
	if ( fd < 0 ) {
		fprintf ( stderr, "Error in file opening...!\n" );
		exit (2);
	}

	acc_no = atoi ( argv [1] );
	if ( acc_no > TOTAL_REC) {
		fprintf ( stderr, "Invalid account number...!\n" );
		exit (3);
	}

	amount = atoi ( argv [2] );
	if ( amount < 1 ) {
		fprintf ( stderr, "Invalid amount...!\n");
		exit (4);
	}

	system ("clear");
	sprintf ( chk_balnce, "balance %d", acc_no ); 
	system ( chk_balnce );	

	printf ( "Your Transaction Initiated...\n" );
	pointer = (acc_no - 1) * sizeof (rec) 
					+ sizeof (rec.name)+ sizeof ( rec.phone )+2;
	if ( lseek ( fd, pointer, SEEK_SET ) < 0 ){
		fprintf ( stderr, "Error in seeking file...!\n" );
		exit (6);	
	}


	/********* semget ***************/
	semd = semget ( KEY, 1, IPC_CREAT | 0777 );
	if ( semd == -1 )
		fprintf (stderr, "Error in Semaphore creation ...\n" );	

	/****** P **********/
	sop.sem_num = 0;
	sop.sem_op 	= -1;
	sop.sem_flg = IPC_NOWAIT;
	while ( ( semop (semd, &sop, 1 ) ) != 0 ){
		printf ("\033[5m PLEASE WAITING....\r\033[0m");
		fflush(stdout);
		sleep (1);
	}

	/********* RMW Cycle ***********/	

	/*** Read ***/
	read ( fd, &rec.balance, sizeof ( rec.balance ) );
	printf ("Old Balance: %d\n", rec.balance);

	sleep (8);

	/*** Modify ***/
	rec.balance -= amount;
	printf ("%d Withdrawn \n", amount );
	printf ("New Balance: %d\n", rec.balance);

	/*** Write ***/
	lseek ( fd, pointer, SEEK_SET );
	write ( fd, &rec.balance, sizeof (rec.balance) );

	/****** V **********/
	sop.sem_num = 0;
	sop.sem_op 	= 1;
	sop.sem_flg = IPC_NOWAIT;
	if ( ( semop (semd, &sop, 1 ) ) == 0 )
		//printf ("semop V successfull...\n" );

	printf ("\033[5m\033[14;10HTRANSACTION SUCCESSFULL...\033[0m\n\n\n");

	system ( chk_balnce );	
	close (fd);
}

