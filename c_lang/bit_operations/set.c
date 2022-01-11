# include <stdio.h>
# include <stdlib.h>

# define set_macro( n , p ) ( ( n ) | ( 1 << ( p ) ) ) 

int set ( int num, int pos );

main ( int argc, char *argv [] ) {
	int num, pos;

	if (argc < 3 ){
		fprintf (stderr, "usage: a.out <num1> <num2>\n");
		exit (1);
	}
	num = atoi (argv [1]); 
	pos = atoi (argv [2]);

	//num = set (num, pos);
	num = set_macro (num, pos);

	printf ("%d", num);
}

int set ( int num, int pos ) {
	num = num | (1 << pos);
	return num;
}

void reset ( int num, int pos ) {
	num = num & ~( 1 << pos );
}

void toggle ( int num, int pos ) {
	num = num ^ (1 << pos);
}
