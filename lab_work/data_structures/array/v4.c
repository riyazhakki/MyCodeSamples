/* v4.c : stratchable arrays 
		Use realloc (3).
*/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define HUGE 20

int *nums;
int *old;

main ( ) {
	int n;
	int i;
//	register int *src;
//	register int *dst;

	
	nums = (int *) malloc ( sizeof ( int ) );
	n = 0;

	while ( 1 ) {
		if ( scanf ( "%d", nums+n ) != 1 )
			break;
		n++;
		//old = nums;
		//nums = ( int * ) malloc ( ( n + 1 )  * sizeof ( int ) );
		 nums = ( int * ) realloc ( (char * )nums, ( n + 1 ) * sizeof ( int ) );

//		src = old;
//		dst = nums;

		//for ( i = 0; i < n; i++ )
		//	nums [ i ] = old [ i ];
			//*dst++ = *src++;			// walking pointer

		//memcpy ( (char *) nums, (char *) old, n * sizeof (int) );


	}

	for ( i = 0; i < n; i++ )
		printf ("%d", nums [ i ] );
}
