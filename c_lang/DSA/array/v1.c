/* v1.c : uses static array */

# define NMAX 10

int nums [ NMAX ];

# include <stdio.h>
# include <stdlib.h>

main ( ) {
	int place;
	int n;

	place = 0;
	while ( place < NMAX )
		if (scanf ( "%d", &nums [place] ) == 1 )
			place++;
		else
			break;
	
	if (!place) {
		fprintf ( stderr, "be serious \n" );
		exit ( 1 );
	}
	n = place;
	for ( place = 0; place < n; place++ )
		printf ("%d", nums [ place ] );
}
