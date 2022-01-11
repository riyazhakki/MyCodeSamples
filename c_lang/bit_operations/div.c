# include <stdio.h>

main ( int argc, char *argv [] ) {
	int n1, n2;	
	int x, y, i;

	x = n1 = atoi (argv[1]);
	y = n2 = atoi (argv[2]);

	for ( i = 0;  x >= y; i++ ){
		while (n2) {
			x = n1 ^ n2;
			n2 = (~n1 & n2 ) << 1;
			n1 = x;
		}
		n2 = y;
	}
	printf ("Q%d\n", i);
	printf ("R%d\n", x);
	printf ("D%d\n", y);
}
