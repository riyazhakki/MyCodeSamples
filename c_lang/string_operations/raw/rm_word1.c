
/*****************************************************************************
rm_word.c:
	Remove all occurences of specified word ( argv[1] ) from input stream.
******************************************************************************/

# include <stdio.h>
# include <stdlib.h>

main ( int argc, char * argv [ ] ) {
	char * temp;
	char preserved [20];
	int c;
	int state;
	int i;

	enum states { MATCHING, MIS_MATCH};

	if ( argc < 2 ) {
		fprintf (stderr, "usage: a.out <pattern>\n" );
		exit (1);
	}

	temp = argv [1];
	state = MATCHING;
	i = 0;

	while ( ( c = getchar () ) != EOF ) {
		switch ( state ) {
			case  MATCHING :
				if ( c == *temp ) {
					preserved [ i++ ] = *temp++;	
					continue;
				}
				else if ( *temp != '\0' ){
					preserved [i] = '\0';
					printf ( "%s", preserved );
					state = MIS_MATCH;
				}
				else {
					preserved [ i = 0 ] = '\0';
					state = MIS_MATCH;
				}
				putchar ( c );
			break;

			case MIS_MATCH:
				if ( c == ' ' || c == '\t' || c == '\n' ) {
					if ( *temp == '\0' ) 
						preserved [ i = 0 ] = '\0';
					state = MATCHING;
					temp = argv [1];
				}
				putchar ( c );
			break;
		}
	}
	return 0;
}

