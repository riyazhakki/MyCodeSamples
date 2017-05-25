# include <stdio.h>
# include "sb.h"

void display ( struct record rec ) {
	printf ( "Name : %s\n", rec.name );
	printf ( "Balance : %d\n", rec.balance );
	printf ( "Phone : %s\n", rec.phone );
}
