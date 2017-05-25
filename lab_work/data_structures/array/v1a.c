/* v1.c : uses static array 
			Accept fractional numbers. */

# define NMAX 10

float nums [ NMAX ];

# include <stdio.h>
# include <stdlib.h>

main ( ) {
	int place;
	int n;

	place = 0;
	while ( place < NMAX )
		if (scanf ( "%f", &nums [place] ) == 1 )
			place++;
		else
			break;
	
	if (!place) {
		fprintf ( stderr, "be serious \n" );
		exit ( 1 );
	}
	n = place;
	for ( place = 0; place < n; place++ )
		printf ("%f", nums [ place ] );
}
