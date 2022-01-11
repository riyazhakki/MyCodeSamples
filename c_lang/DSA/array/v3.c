/* v3.c : stratchable arrays */

# include <stdio.h>
# include <stdlib.h>

# define HUGE 20

int *nums;
int *old;

main ( ) {
	int n;
	int i;
	
	nums = (int *) malloc ( sizeof ( int ) );
	n = 0;

	while ( 1 ) {
		if ( scanf ( "%d", nums+n ) != 1 )
			break;
		n++;
		old = nums;
		nums = ( int * ) malloc ( ( n + 1 )  * sizeof ( int ) );
		for ( i = 0; i < n; i++ )
			nums [ i ] = old [ i ];
	}

	for ( i = 0; i < n; i++ )
		printf ("%d", nums [ i ] );
}
