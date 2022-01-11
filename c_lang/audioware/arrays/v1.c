/* STATIC ARRAYS size known priori */

# include <stdio.h>
# include <stdlib.h>

# define NMAX 50

int nums [NMAX];

main(){

	int place;
	int n;

	place = 0;
	while (place < NMAX && scanf ("%d", nums + place) == 1)
		place++;
	n = place;
	for (place = 0; place < n; place ++)
		printf ("Your number = %d\n", nums[place]);
	exit (0);
}


