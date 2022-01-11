# include <stdio.h>
# include <stdlib.h>

main ( ) {
	
	int  n;
	int *p;
	int i;

	printf ( "Enter the stack:" );
	scanf ( "%d", & n);

	p =  (  int * ) malloc ( n  * sizeof ( int ) );
	
	for ( i = 0; i < n; i++ ) {
		scanf ( "%d", p + i );
	}

//	for ( i = 0; i < n; i++)
}
