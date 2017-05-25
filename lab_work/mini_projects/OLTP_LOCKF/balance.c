/* Display Balance */

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "sb.h"

void display ( struct record rec );

main ( int argc, char *argv [ ] ) {
	int acc_no;
	int fd;
	struct record rec;

	if ( argc < 2 ) {
		fprintf ( stderr, "<balance> <acc_no.>\n" );
		exit (1);
	}

	fd = open ( "master.dat", O_RDONLY );
	if ( fd < 0 ) {
		fprintf ( stderr, "File cannot open...!\n" );
		exit (3);
	}

	printf ("Total: %d\n", TOTAL_REC );
	acc_no = atoi ( argv [1] );
	if ( acc_no > TOTAL_REC) {
		fprintf ( stderr, "Invalid account number...!\n" );
		exit (2);
	}
	
	acc_no = (acc_no - 1) * sizeof (rec);
	if ( lseek ( fd, acc_no, SEEK_SET ) < 0 ){
		fprintf ( stderr, "Error in seeking file...!\n" );
		exit (3);	
	}

	read ( fd, &rec, sizeof (rec) );
	display (rec);
	close (fd);
}
