/* Change phone no.*/

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <ctype.h>
# include <string.h>
# include "sb.h"

main ( int argc, char *argv [ ] ) {
	//char chk_balnce [20];
	int fd;
	int acc_no;
	char phone [11];
	int pointer;
	struct record rec;

	if ( argc < 3 ) {
		fprintf ( stderr, " <change> <acc_no.> <phone_no.> \n" );
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

	strcpy ( phone , argv [2] );


	if ( strlen (phone) != 10 ) {
		fprintf ( stderr, "Invalid phone number...!\n");
		exit (4);
	}

	system ("clear");
	//sprintf ( chk_balnce, "balance %d", acc_no ); 
	//system ( chk_balnce );	

	printf ( "Your Transaction Initiated...\n" );
	pointer = (acc_no - 1) * sizeof (rec) 
					+ sizeof (rec.name);
	if ( lseek ( fd, pointer, SEEK_SET ) < 0 ){
		fprintf ( stderr, "Error in seeking file...!\n" );
		exit (6);	
	}

	/*** LOCKING ****/
	while ( lockf ( fd, F_TLOCK, sizeof ( rec.phone ) ) == -1 ){
		printf ( "\nsome transcation in process\n" );
		printf ( "\033[5m     PLEASE WAIT...\033[0m\n" );
		sleep (4);
	}


	/********* RMW Cycle ***********/	
	sleep (8);

	/*** Read ***/
	read ( fd, &rec.phone, sizeof (rec.phone)+2 );
	printf ("Old Phone: %s\n", rec.phone);

	/*** Modify ***/
	strcpy (rec.phone, phone);
	printf ("New Phone: %s\n", rec.phone);

	/*** Write ***/
	lseek ( fd, pointer, SEEK_SET );
	write ( fd, &rec.phone, sizeof (rec.phone) );

	/*** UNLOCKING ****/
	lseek ( fd, pointer, SEEK_SET );
	lockf ( fd, F_ULOCK, sizeof (rec.name) );
	
	printf ( "\n\n\033[5m TRANSACTION SUCCESSFULL...\033[0m\n\n\n" );

	//system ( chk_balnce );	
	close (fd);
}

