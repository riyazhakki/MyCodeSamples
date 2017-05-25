# include <stdio.h>
# include "sb.h"

void display ( struct record rec ) {
	int i;
	for ( i = 0; i< 20; i++ )
	printf ("\033(0q\033(B");
	printf ( "\nName : %s\n", rec.name );
	printf ( "Balance : %d\n", rec.balance );
	printf ( "Phone : %s\n", rec.phone );
	for ( i = 0; i< 20; i++ )
	printf ("\033(0q\033(B");
	putchar ('\n');
}
