/* ex19_chktty.c:	Run program in the following ways: ( read man isatty )
	a) cc ex19_chktty.c
	b) a.out
	c) a.out | more
	d) a.out > xxxx
		cat xxxx
	e) vi xxx
		a.out < xxx
	f) a.out < xxx > yyy
		cat yyy
	g) Try removing isatty() check and do scanf directly 
	---------------------------------------------------------------------*/

# include <stdio.h>

int main () {
	FILE * ttyfd; int x;

	if ( isatty (1) )
		printf ( "This comes on the display\n" );
	else 
		printf ( "This goes to a file / pipe \n");
	
	if ( isatty (0) ) {	// parameter 0 / 1 has same effect
		printf ( "Enter number :" );
		scanf ( "%d", &x );
		printf ( "Value accepted is %d\n", x);
	} else {
		ttyfd = fopen ( "/dev/tty", "r+" );
		fprintf ( ttyfd, "%s", "Enter number :" );
		fscanf ( ttyfd, "%d", &x );
		printf ( "Value accepted is %d\n", x );
	}
}

