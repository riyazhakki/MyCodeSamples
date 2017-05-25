/* v2a_sort.c : dynamic arrays 
	Ritchie C book has given Shell sort program to sort an array (of int's).
	Upgrade v2.c to print the typed numbers in ascending order.
*/

# include <stdio.h>
# include <stdlib.h>

# define HUGE 20

int nmax; 
int *nums;
int place; 
int n;

void shellsort ( int *, int  );

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
	shellsort ( nums, n );
	putchar ('\n');
	for ( place = 0; place < n; place++ )
		printf ("%d\n", nums [ place ] );
}

void shellsort ( int v [ ], int n ) {
	int gap, i, j, temp;

	for ( gap = n/2; gap > 0; gap /= 2 )
		for ( i = gap; i < n; i++ )
			for ( j = i - gap; j >= 0 && v [ j ] > v [ j + gap ]; j -= gap ) {
				temp = v [ j ];
				v [ j ] = v [ j + gap ];
				v [ j + gap ] = temp;
			}
}
