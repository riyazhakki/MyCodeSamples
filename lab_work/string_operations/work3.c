/* work3.c
	To remove occurences of the word 'for' from the input stream.  we employ the state machine with the states as shown in the #define's.
	*/

# include <stdio.h>


# define WAITING_FOR_F	0
# define GOT_F			1
# define GOT_FO			2
# define GOT_FOR		3
# define GOT_WRONG		4
# define WHITE(c)	(( c ==' ' ) || ( c == '\t') || ( c == '\n' ))

main () {
	int state = WAITING_FOR_F; 
	int c;

	while ( ( c = getchar () ) != EOF ) {
		switch ( state ) {
			case WAITING_FOR_F:
				if ( c == 'f')
					state = GOT_F;
				else {
					putchar ( c );
					if ( WHITE (c) ) 
						state = GOT_WRONG;
				}
			break;
			case GOT_F:
				if ( c == 'o')
					state = GOT_FO;
				else {
					putchar ( 'f' );
					putchar ( c );
					if ( WHITE (c) ) 
						state = WAITING_FOR_F;
					else
						state = GOT_WRONG;

				}
				break;
			case GOT_FO:
				if ( c == 'r')
					state = GOT_FOR;
				else {
					putchar ( 'f' );
					putchar ( 'o' );
					putchar ( c );
					if ( WHITE (c) ) 
						state = WAITING_FOR_F;
					else
						state = GOT_WRONG;
				}
				break;
			case GOT_FOR:
					if ( WHITE (c) ) 
						state = WAITING_FOR_F;
					else
						state = GOT_WRONG;
				break;
			case GOT_WRONG:
					putchar ( c );
					if ( WHITE (c) ) 
						state = WAITING_FOR_F;
			break;
		}
	}
}
