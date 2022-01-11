/* 1. Find size of an int without using sizeof operator. */

# include <stdio.h>

main () {
	int x = 0;
	int count = 0;

	x = ~x;				// 1's complement become 1111..11
	while (x) {
		x = x << 1;   //don't do right shift msb will be shifted
		count++;
	}
	printf ("size of int is : %d\n", count);
}
