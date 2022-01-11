/* v4a_test.c : stratchable arrays 
	Use realloc ( 3 ).
	Change value of ROQ and notice the effect onload test timings.
*/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define ROQ 10

int *nums;
int *old;

main ( ) {
	int n;
	int i;
	int j;
	//register int *src;
	//register int *dst;

	
	nums = (int *) malloc ( sizeof ( int ) );
	n = 0;

	while ( 1 ) {
		for ( j = 0; j < 10000 && j <= n; j++ )
			nums [ j ] = j;

		if ( n > 10000 )
			break;

		//old = nums;
		//nums = ( int * ) malloc ( ( n + 1 )  * sizeof ( int ) );
		if ( ( n % ROQ ) == 0 )
			nums =(int *) realloc((char * )nums, ( n + ROQ ) * sizeof ( int ));

		n++;

		//src = old;
		//dst = nums;

		//for ( i = 0; i < n; i++ )
		//	nums [ i ] = old [ i ];
			//*dst++ = *src++;			// walking pointer

		//memcpy ( (char *) nums, (char *) old, n * sizeof (int) );
	}

	for ( i = 0; i < n; i++ )
		printf ("%d", nums [ i ] );
}
