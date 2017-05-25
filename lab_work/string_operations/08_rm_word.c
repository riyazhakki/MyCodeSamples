
/*****************************************************************************
rm_word.c:
	Remove all occurences of specified word ( argv[1] ) from input stream.
******************************************************************************/

# include <stdio.h>
# include <stdlib.h>

main ( int argc, char * argv [ ] ) {
	int c;
	char * temp;
	char preserved [20];
	int count;
	int flag;
	int i = 0;

	# define MATCHING 0	
	# define MIS_MATCH 1	

	if ( argc < 2 ) {
		fprintf (stderr, "usage: a.out <pattern>\n" );
		exit (1);
	}
	temp = argv [1];
	count = 0;
	flag = MATCHING;

	while ( ( c = getchar () ) != EOF ) {
		if ( c == ' ' || c == '\t' || c == '\n' ) {
			if ( *temp == '\0' ) {
				count ++;
				i = 0;
				preserved [ i ] = '\0';
			}
			temp = argv [1];
			flag = MATCHING;
			putchar ( c );
		}
		else { 
			if ( flag == MATCHING )	{
				if ( c == *temp ) {
					preserved [ i++ ] = *temp++;	
					continue;
				}
				else {
					preserved [i] = '\0';
					printf ( "%s", preserved );
					flag = MIS_MATCH;
				}
			}
				putchar ( c );
		}
	}
	return 0;
}

