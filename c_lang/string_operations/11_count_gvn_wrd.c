/*****************************************************************************
count_res_wrd.c:
	Count the number of each of the argvs in the input.
	The argvs to be counted are : argv [1], argv [2], ... argv [argc -1].
*****************************************************************************/

# include <stdio.h>
# include <stdlib.h>

# define NWORDS 20

main ( int argc, char * argv [ ] ) {
	char * temp [ NWORDS ];
	int count [ NWORDS ];
	int c, i, flag [ NWORDS ];

	# define MATCHING 	0
	# define MIS_MATCH 	1

	if ( argc < 2 ) {
		fprintf (stderr, "usage: a.out <pattern1> .... \n");
		exit (1);
	}
	for ( i = 1; i < argc; i++ ) {
		temp [ i ] = argv [ i ];
		flag [ i ] = MIS_MATCH;
		count [ i ] = 0;
	}

	while ( ( c = getchar ( ) ) != EOF ) {
		for ( i = 1; i < argc; i++ ) {
			if ( c == ' ' || c == '\t' || c == '\n' ) {
				if ( *temp [ i ] == '\0' ) 
					count [i]++;
				flag [i] = MATCHING;	
				temp [i] = argv [i];	
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
	for ( i = 1; i < argc; i++ ) 
		printf ( "%s: occurs %d times\n", argv [i], count[i] );
	return 0;
}
