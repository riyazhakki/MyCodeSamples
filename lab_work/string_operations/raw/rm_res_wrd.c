/*****************************************************************************
rm_res_wrd.c:
		Remove all occurences of the reserved res_words from input. (assign4.c)
*****************************************************************************/

# include <stdio.h>

main ( ) {
	char * res_word [ 8 ] = { "for", "while", "case", "switch", "if", "else", 
							"break", "continue" };
	char * temp [ 8 ];
	int count [ 8 ];
	int c, i, flag [ 8 ];

	# define MATCHING 	0
	# define MIS_MATCH 	1

	for ( i = 0; i < 8; i++ ) {
		temp [ i ] = res_word [ i ];
		flag [ i ] = MIS_MATCH;
		count [ i ] = 0;
	}

	while ( ( c = getchar ( ) ) != EOF ) {
		for ( i = 0; i < 8; i++ ) {
			if ( c == ' ' || c == '\t' || c == '\n' ) {
				if ( *temp [ i ] == '\0' ) 
					count [i]++;
				flag [i] = MATCHING;	
				temp [i] = res_word [i];	
			}
			else {
				if ( flag [i] == MATCHING ) {
					if ( c == *temp [i] ) { 
						temp [i]++;
					}
					else
						flag [i] = MIS_MATCH;
				}

			}
		}
			putchar (c);
	}
	return 0;
}
