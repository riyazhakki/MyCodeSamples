/* Display 4 digit number which does not contain zeros and only contain
	1,2,3 and 4 as digits at any position */
# include <stdio.h>

main () {
	int i, j;

	for (i = 1111; i < 9999; i++ ) {
		for ( j = i; j; j /= 10 )
			if ( j % 10 == 0 )
				break;
		if ( !j )
			printf("%d\n", i);
	}
}
