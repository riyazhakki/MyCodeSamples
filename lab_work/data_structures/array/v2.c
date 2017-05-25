/* v2.c : dynamic arrays */

# include <stdio.h>
# include <stdlib.h>

# define HUGE 20

int nmax; 
int *nums;
int place; 
int n;

main ( ) {

	printf ("no. of ints = ");

	if (scanf ("%d", &nmax ) != 1 ) {
		fprintf ( stderr, "don't play here\n" );
		exit ( 1 );
	}
	if ( nmax < 1 || nmax > HUGE ) {
		fprintf ( stderr, "why don't you be serious\n" );
		exit ( 2 );
	}

	nums = ( int * ) malloc ( nmax * sizeof * nums );

	place = 0;
	while ( place < nmax )
		if ( scanf ("%d", nums+place ) == 1 )
			place++;
		else
			break;
	if ( !place ) {
		fprintf ( stderr, " be serious\n" );
		exit ( 3 );
	}
	n = place;
	for ( place = 0; place < n; place++ )
		printf ("%d", nums [ place ] );
}
