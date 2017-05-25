# include <stdio.h>
# include <stdlib.h>

int main (int argc, char *argv[] ) {
	unsigned int x, y, sum, carry;

	if (argc < 3 ){
		fprintf (stderr, "usage: a.out <num1> <num2>\n");
		exit (1);
	}
	x = atoi (argv[1]);
	y = atoi (argv[2]);

	sum = x ^ y;
	carry = x & y;

	while ( carry ) {
		carry = carry << 1;
		x = sum;
		y = carry;
		sum = x ^ y;
		carry = x & y;
	}
		printf (" sum = %d\n", sum );
}
