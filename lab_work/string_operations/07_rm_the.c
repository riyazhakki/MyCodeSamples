/* work3.c
	To remove occurences of the word 'the' from the input stream.  we employ the state machine with the states as shown in the #define's.
	*/

# include <stdio.h>


# define WAITING_FOR_T	0
# define GOT_T			1
# define GOT_TH			2
# define GOT_THE		3
# define GOT_WRONG		4
# define WHITE(c)	(( c ==' ' ) || ( c == '\t') || ( c == '\n' ))

main () {
	int state = WAITING_FOR_T; 
	int c;

	while ( ( c = getchar () ) != EOF ) {
		switch ( state ) {
			case WAITING_FOR_T:
				if ( c == 't')
					state = GOT_T;
				else {
					putchar ( c );
					if ( WHITE (c) ) 
						state = GOT_WRONG;
				}
			break;
			case GOT_T:
				if ( c == 'h')
					state = GOT_TH;
				else {
					putchar ( 't' );
					putchar ( c );
					if ( WHITE (c) ) 
						state = WAITING_FOR_T;
					else
						state = GOT_WRONG;

				}
				break;
			case GOT_TH:
				if ( c == 'e')
					state = GOT_THE;
				else {
					putchar ( 't' );
					putchar ( 'h' );
					putchar ( c );
					if ( WHITE (c) ) 
						state = WAITING_FOR_T;
					else
						state = GOT_WRONG;
				}
				break;
			case GOT_THE:
					if ( WHITE (c) ) 
						state = WAITING_FOR_T;
					else
						state = GOT_WRONG;
				break;
			case GOT_WRONG:
					putchar ( c );
					if ( WHITE (c) ) 
						state = WAITING_FOR_T;
			break;
		}
	}
}
