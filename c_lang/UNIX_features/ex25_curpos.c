/* Find out cursor positioning escape sequence 
Draw rectangle of *'s on screeen given width and height  */

# include <stdio.h>
# include <stdlib.h>

main ( ) {
	int w = 4 , c = 40, i, j;

	system ("clear");
	for ( i = 0; i <= w; i++){ 
		for ( j = 0; j < c; j++ ){
			if ( i == 0 || j == 0 || j == c - 1 || i == w ) {
				printf ("\033[%d;%dH*", i, j);	
			}
		}
		putchar ('\n');
	}
		putchar ('\n');
}
