/* Open account */

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "sb.h"

void write_rec ( void );
void read_rec ( void );

struct record rec;
int fd;
int t;

main ( ) {

	printf ( "%d\n", sizeof (struct record ));

	fd =	open ( "master.dat", O_CREAT | O_APPEND | O_RDWR, 0744 );

	if ( fd == -1 ) {
		fprintf ( stderr, "Error in file opening...!\n " );
		exit (1);
	}
	write_rec ();
	read_rec ();
	close (fd);
}

void write_rec ( ) {

	rec.flag = ACTIVE;
	printf ( "Name :");
	scanf ( "%s", rec.name );
	printf ( "Balance: %d\n",rec.balance = 1000);
	printf ( "Phone Number:" );
	scanf ( "%s", rec.phone );

	t = write ( fd, &rec, sizeof (struct record) );
	if ( t < 0 ) {
		fprintf ( stderr, "Error in writing....!\n");
		exit (2);
	}
}

void read_rec ( ) {
	read ( fd, &rec, sizeof (rec) );
	printf ("Name: %s\n", rec.name );
	printf ("Balance: %d\n", rec.balance );
	printf ("Phone No.: %s\n", rec.phone );
}
