/*****************************************************************************
count_the.c:
	To count the number of occurences of the word "the" in the input and print
the same.
******************************************************************************/

# include <stdio.h>
# include <stdlib.h>

main ( ) {
	int c;
	char * str = "the";
	char * temp;
	int count;
	int flag;

	# define MATCHING 0	
	# define MIS_MATCH 1	

	temp = str;
	count = 0;
	flag = MATCHING;

	while ( ( c = getchar () ) != EOF ) {
		if ( c == ' ' || c == '\t' || c == '\n' ) {
			if ( *temp == '\0' )
				count ++;
			temp = str;
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
	printf ("%-10s: occurs %d times\n", str, count );
	return 0;
}

