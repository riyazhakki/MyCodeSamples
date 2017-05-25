# include <stdio.h>

main ( int argc, char *argv [] ) {
	int n1, n2;	
	int x;

	n1 = atoi (argv[1]);
	n2 = atoi (argv[2]);

	while (n2) {
		x = n1 ^ n2;
		n2 = (~n1 & n2 ) << 1;
		n1 = x;
	}

	printf ("%d\n", n1);
}
