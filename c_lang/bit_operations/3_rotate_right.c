/* 3. Rotate an integer right by n places  */

# include <stdio.h>
# include <stdlib.h>

int rotate_bits (int, int);

main (int argc, char *argv[]) {
	int number, rotation;
	int i, j;

	if (argc < 2) {
		fprintf (stderr, "Usage: <integer> <rotation>\n");
		exit (1);
	}

	for ( i = 1; i <=2; i++) {
		for ( j = 0; argv [i][j] != '\0'; j++) {
			if ( ! isdigit (argv [i][j])) {
				fprintf (stderr, "Either of your input is not integer....!\n");
				exit (2);
			}
		}
	}

	number = atoi (argv[1]);
	rotation = atoi (argv[2]);

	number = rotate_bits (number, rotation);
	printf ("%d\n", number);
}

int rotate_bits (int x, int r) {
	int mask;
	int lsb;

	mask = 1 << (sizeof (int) * 8 - 2);		// 100...0

	while (r--) {
		lsb = x & 1;
		x >>= 1;
		if (lsb)
			x |= mask;
	} 
	return x;
}
