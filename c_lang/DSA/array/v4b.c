/* v4b.c : uses tunable array */

extern int nmax;
extern int nums [ ];

# include <stdio.h>
# include <stdlib.h>

main ( ) {
	int place;
	int n;

	place = 0;
	while ( place < nmax )
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
