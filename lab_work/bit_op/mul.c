# include <stdio.h>
# include <stdlib.h>

main ( int argc, char *argv [] ) {
	int n1, n2;	
	int x = 0, i;

	if (argc < 3 ){
		fprintf (stderr, "usage: a.out <num1> <num2>\n");
		exit (1);
	}
	n1 = atoi (argv[1]);
	n2 = atoi (argv[2]);

	for ( i = 0; i < 32; i++) {
		if (( n1 >> i) & 1)
			x += n2 << i;
	}
	printf ("%d\n", x);

	/**********************OR*************
	for ( i = 0; n1; n1 >>= 1, n2 <<= 1) {
		if ( n1 & 1 )
			i += n2;
	}
	printf ("%d\n", i); 
	***********************/
}

