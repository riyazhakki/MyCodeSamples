 
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

char *reserved [] = {
	"if", "for", "while", "break", "continue", NULL
};

# define 	WHITE(c) ((c ==' ') || (c=='\t') || (c=='\n'))

enum states { IN_WHITE_SPACE, IN_WORD, IN_LONG_WORD };

int *count;
char *word;
int now;

main ( ) {
	int c, j, cur_size;
	int state = IN_WHITE_SPACE;
	int l = 0;
	
	for (now = 0; reserved [ now ]; now++) {
		if ( strlen ( reserved [ now ] ) > l )
			l = strlen ( reserved [ now ] );
	}
	word = malloc ( l + 1 );
	count = ( int* ) malloc ( now * sizeof ( int ) );

	for( j = 0; j < now; j++ ) 
		count [ j ] = 0;

	while ( ( c = getchar () ) !=  EOF ) {
		switch ( state ) {
			case IN_WHITE_SPACE:
				if ( WHITE ( c ) )
					break ;
				state = IN_WORD;
				cur_size = 0;
				word [ cur_size++ ] = c;
				break ;
			case IN_WORD:
				if ( !WHITE ( c ) )
					if ( cur_size == l ) {
						state = IN_LONG_WORD;
						break ;
					}
					else {
						word[cur_size++]=c;
						break ;
					}
					state = IN_WHITE_SPACE;
					word [ cur_size ] =  '\0';
					for ( j = 0; j < now; j++)
						if ( strcmp ( word, reserved [ j ] ) == 0 ) {
							count[j]++;
							break ;
						}
						break ;
				case IN_LONG_WORD:
					if ( WHITE ( c ) )  
						state = IN_WHITE_SPACE;
							break ;
			}
	}
	for ( j = 0; j < now; j++ )
		printf ( "No.of Occurancesof %s =  %d\n", 
			reserved[j], count[j] );
}
