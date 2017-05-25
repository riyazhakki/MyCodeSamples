/* Deposit amount */

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <ctype.h>
# include "sb.h"

main ( int argc, char *argv [ ] ) {
	char chk_balnce [20];
	int fd;
	int acc_no;
	int amount;
	int pointer;
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

	/*** LOCKING ****/
	while ( lockf ( fd, F_TLOCK, sizeof ( rec.balance ) ) == -1 ){
		printf ( "\033[7;10H some transcation in process\n" );
		printf ( "\033[8;14H \033[5m     PLEASE WAIT...\033[0m\n" );
		sleep (4);
	}


	/********* RMW Cycle ***********/	

	/*** Read ***/
	read ( fd, &rec.balance, sizeof ( rec.balance ) );
	printf ("Old Balance: %d\n", rec.balance);

	sleep (8);
	/*** Modify ***/
	rec.balance += amount;
	printf ("New Balance: %d\n", rec.balance);

	/*** Write ***/
	lseek ( fd, pointer, SEEK_SET );
	write ( fd, &rec.balance, sizeof (rec.balance) );

	/*** UNLOCKING ****/
	lseek ( fd, pointer, SEEK_SET );
	lockf ( fd, F_ULOCK, sizeof (rec.balance) );
	
	printf ( "\033[5m\033[14;10H TRANSACTION SUCCESSFULL...\033[0m\n\n\n" );

	system ( chk_balnce );	
	close (fd);
}

