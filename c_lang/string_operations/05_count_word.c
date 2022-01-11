/*****************************************************************************
count_the.c:
	To count the number of occurences of the given word. (argv [1]) 
******************************************************************************/

# include <stdio.h>
# include <stdlib.h>

main ( int argc, char * argv [ ] ) {
	int c;
	char * temp;
	int count;
	int flag;

	# define MATCHING 0	
	# define MIS_MATCH 1	

	if ( argc < 2 )
		exit (1);
	temp = argv [1];
	count = 0;
	flag = MATCHING;

	while ( ( c = getchar () ) != EOF ) {
		if ( c == ' ' || c == '\t' || c == '\n' ) {
			if ( *temp == '\0' )
				count ++;
			temp = argv [1];
			flag = MATCHING;
		}
		else { 
			if ( flag == MATCHING )	{
				if ( c == *temp ) 
					temp ++;
				else
					flag = MIS_MATCH;
			}
		}
	}
	printf ("%-10s: occurs %d times\n", argv [1], count );
	return 0;
}

