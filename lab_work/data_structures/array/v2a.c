/* v2a.c : dynamic arrays:
		a> total of all numbers typed
		b> arithemetic mean ( average ) of numbers
		c> maximum mumber typed
		d> minimum number typed
		e> maximum absolute value typed
*/

# include <stdio.h>
# include <stdlib.h>

# define HUGE 20

int nmax; 
int *nums;
int place; 
int n;
int sum;
int avg;
int max;
int min;

main ( ) {

	printf ( "no. of ints = " );

	if (scanf ( "%d", &nmax ) != 1 ) {
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

	min = nums [ 0 ];
	for ( place = 0; place < n; place++ ) {
		sum += nums [ place ];
		if ( max < nums [ place ] )
			max = nums [ place ];
		if ( min > nums [ place ] )
			min = nums [ place ];

	}
	avg = sum / n;

	printf ( "Total of all numbers typed: %d\n", sum );
	printf ( "Arithemetic mean ( average ) of numbers is: %d\n", avg );
	printf ( "Maximum number typed is: %d\n", max );
	printf ( "Minimum number typed is: %d\n", min );
	printf ( "Maximum absolute value typed is: %d\n", max );
}
