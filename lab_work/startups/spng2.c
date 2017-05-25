/* Display 4 digit number which does not contain zeros and only contain
	1,2,3 and 4 as digits at any position */

# include <stdio.h>

main () {
	int i, j, flag; 

	for (i = 1111; i <= 4444; i++, flag = 1){
		for (j = i; j > 0; j /= 10){
			if (j % 10 == 0 || j % 10 > 4){
				flag = 0;
				break;
			}
		}
		if ( flag )		
			printf ("%d\t", i);
	}
}
