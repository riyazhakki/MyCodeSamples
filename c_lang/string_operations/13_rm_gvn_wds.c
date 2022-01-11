/****************************************************************************
13_rm_gvn_wds.c:
	Remove all occurences of given words from input.
****************************************************************************/
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define 	WHITE(c) ((c ==' ') || (c=='\t') || (c=='\n'))

enum states { IN_WHITE_SPACE, IN_WORD, IN_LONG_WORD };

int found = 0;

main ( int argc, char * argv [ ] ) {
	int c, j, cur_size;
	int state = IN_WHITE_SPACE;
	char word [ 80 ];

	argv++;	argc--; 
	while ( ( c = getchar () ) !=  EOF ) {
		switch ( state ) {
			case IN_WHITE_SPACE:
				if ( WHITE ( c ) ){
					putchar (c);
					break ;
				}
				state = IN_WORD;
				found = 0;
				cur_size = 0;
				word [ cur_size++ ] = c;
			break ;
			case IN_WORD:
				if ( !WHITE ( c ) ) {
						word [ cur_size++ ] = c;
						break ;
					}
					putchar (c);
					state = IN_WHITE_SPACE;
					word [ cur_size ] =  '\0';
					for ( j = 0; j < argc; j++) {
						if ( strcmp ( word, argv [ j ] ) == 0 ) {
							found = 1;
							break ;
						}
					}
					if (!found)
						printf ("%s", word );
				break ;
			}
	}
}
