/* Deposit amount */

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <ctype.h>
# include "sb.h"

void display ( struct record rec );
char c;

main ( int argc, char *argv [ ] ) {
	int fd;
	int acc_no;
	int lacc_no;
	int amount;
	int i;
	int pointer;
	struct record rec;
	struct record rec1;

	if ( argc < 2 ) {
		fprintf ( stderr, "<balance> <acc_no.>\n" );
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


	acc_no = atoi ( argv [1] );
	pointer = (acc_no - 1) * sizeof (rec);
	printf ("pointer :%d\n", pointer );
	lseek ( fd, pointer, SEEK_SET );
	read ( fd, &rec1.name, sizeof ( rec1.name ));
	printf ("Name: %s\n", rec1.name);

	acc_no = atoi ( argv [1] );
	pointer = (acc_no - 1) * sizeof (rec) + sizeof (rec.name);
	printf ("pointer :%d\n", pointer );
	lseek ( fd, pointer, SEEK_SET );
	read ( fd, &rec1.phone, sizeof (rec1.phone));
	printf ("Phone: %s\n", rec1.phone);

	acc_no = atoi ( argv [1] );
	pointer = (acc_no - 1) * sizeof (rec) 
					+ sizeof (rec.name)+ sizeof ( rec.phone )+2;
	printf ("pointer :%d\n", pointer );
	lseek ( fd, pointer, SEEK_SET );
	read ( fd, &rec1.balance, 4);
	printf ("Balance: %d\n", rec1.balance);

		printf ("\n\n");


	//read ( fd, &rec1, sizeof (rec1) );
	//display (rec1);

/*
	printf ( "Your Transaction Initiated...\n" );

	lacc_no = acc_no + sizeof (rec.name);

	if ( lseek ( fd, lacc_no, SEEK_SET ) < 0 ){
		fprintf ( stderr, "Error in seeking file...!\n" );
		exit (6);	
	}

	while ( lockf ( fd, F_TLOCK, sizeof(rec.balance) )== -1 ){
		printf ( "wait some transaction in process...\n" );
		sleep (3);
	}

	if ( lseek ( fd, lacc_no, SEEK_SET ) < 0 ){
		fprintf ( stderr, "Error in seeking file...!\n" );
		exit (6);	
	}

	sleep (7);
	lseek ( fd, lacc_no, SEEK_SET );
	printf ("rec.balance:%d\n", rec.balance );
	read ( fd, &rec.balance, sizeof (rec.balance) );
	printf ("rec.balance:%d\n", rec.balance );
	lseek ( fd, lacc_no, SEEK_SET );
	rec.balance += amount;
	write ( fd, &rec.balance, sizeof (rec.balance) );
	lseek ( fd, lacc_no, SEEK_SET );
	lockf ( fd, F_ULOCK, sizeof (rec.balance) );

	printf ( "Your Transaction completed.\n" );

	putchar ('\n');
	lseek ( fd, acc_no, SEEK_SET );
	read ( fd, &rec1, sizeof (rec) );
	display (rec1);

	*/
	close (fd);
}

