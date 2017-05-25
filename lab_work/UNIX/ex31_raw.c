/* Recognise arrow keys and editing keys.
Modify the program to handle additional special keys. 

Do raw I/O from keyboard and return ArrowKey strokes as suitable integer values
to be used by the application   
program files:
	ex31_rawio.h
	ex31_rawio.c
	ex31_raw.c       */

# include <stdio.h>
# include <stdlib.h>
# include "ex31_rawio.h"

# define beep() printf ("\007\007\007\007");

main ( ) {
	int c;
	raw ();
	printf ("Accepting only digits\r\n");
	printf ("Enter any codes; Q to end\r\n" );
	fflush (stdout);
	while ( ( c = get_char () ) != EXIT_PROGRAM ) {
		if ( c >= '0' && c <= '9' ) putchar (c);
		else beep ();
		fflush ( stdout );
	}
	printf ("\r\nEnter any characters ( incl.Arrows ); \r\n" );
	printf ("Q to end :");
	while ( (c = get_char () ) != EXIT_PROGRAM ){
		if ( c < 1000 ) 
			if ( c >= ' ' ) putchar (c);
			else printf ( "^%c", c + '@' );
		else printf ("<%d>", c);
		fflush ( stdout );
	}
	canonical ();
	printf ("\n bye bye\n");
}


