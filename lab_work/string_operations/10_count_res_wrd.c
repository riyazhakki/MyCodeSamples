/*****************************************************************************
count_res_wrd.c:
	Count the number of each of the following reserved words in the input:
		for, while, case, switch, if, else, break, continue. (work4.c)
*****************************************************************************/

# include <stdio.h>

main ( ) {
	char * word [ 8 ] = { "for", "while", "case", "switch", "if", "else", 
							"break", "continue" };
	char * temp [ 8 ];
	int count [ 8 ];
	int c, i, flag [ 8 ];

	# define MATCHING 	0
	# define MIS_MATCH 	1

	for ( i = 0; i < 8; i++ ) {
		temp [ i ] = word [ i ];
		flag [ i ] = MIS_MATCH;
		count [ i ] = 0;
	}

	while ( ( c = getchar ( ) ) != EOF ) {
		for ( i = 0; i < 8; i++ ) {
			if ( c == ' ' || c == '\t' || c == '\n' ) {
				if ( *temp [ i ] == '\0' ) 
					count [i]++;
				flag [i] = MATCHING;	
				temp [i] = word [i];	
			}
			else {
				if ( flag [i] == MATCHING ) {
					if ( c == *temp [i] ) 
						temp [i]++;
					else
						flag [i] = MIS_MATCH;
				}

			}
		}
	}
	for ( i = 0; i < 8; i++ ) 
		printf ( "%s: occurs %d times\n", word [i], count[i] );
	return 0;
}
