/*****************************************************************************
count_the_and.c:
	To count the number of occurences of the word "the" and "and" in the 
input and print the same. A state machine approch can be used.
******************************************************************************/

# include <stdio.h>
# include <stdlib.h>

main ( ) {
	int c;
	int count_the;
	int count_and;
	int state;

	enum states { WAITING_FOR_T_OR_A, GOT_T, GOT_A, GOT_TH, GOT_THE, 
					GOT_AN, GOT_AND, GOT_WRONG };

	count_the = 0;
	count_and = 0;
	state = WAITING_FOR_T_OR_A;

	while ( ( c = getchar () ) != EOF ) {
		switch ( state ) {
			case WAITING_FOR_T_OR_A:
				if ( c == 't' || c == 'T' )
					state = GOT_T;
				else if ( c == 'a' || c == 'A' )
					state = GOT_A;
				else if ( c == ' ' || c == '\t' || c == '\n' )
					state = WAITING_FOR_T_OR_A;
				else 
					state = GOT_WRONG;
				break;
			case GOT_T:
				if ( c == 'h' || c == 'H' )
					state = GOT_TH;
				else if ( c == ' ' || c == '\t' || c == '\n' )
					state = WAITING_FOR_T_OR_A;
				break;
			case GOT_TH:
				if ( c == 'e' || c == 'E' )
					state = GOT_THE;
				else if ( c == ' ' || c == '\t' || c == '\n' )
					state = WAITING_FOR_T_OR_A;
				else 
					state = GOT_WRONG;
				break;
			case GOT_THE:
					count_the++;
					state = WAITING_FOR_T_OR_A;
				break;
			case GOT_A:
				if ( c == 'n' || c == 'N' )
					state = GOT_AN;
				else if ( c == ' ' || c == '\t' || c == '\n' )
					state = WAITING_FOR_T_OR_A;
				else 
					state = GOT_WRONG;
				break;
			case GOT_AN:
				if ( c == 'd' || c == 'D' )
					state = GOT_AND;
				else if ( c == ' ' || c == '\t' || c == '\n' )
					state = WAITING_FOR_T_OR_A;
				else 
					state = GOT_WRONG;
				break;
			case GOT_AND:
					count_and++;
					state = WAITING_FOR_T_OR_A;
				break;
			case GOT_WRONG:
				if ( c == ' ' || c == '\t' || c == '\n' )
					state = WAITING_FOR_T_OR_A;
				break;
		}

	}
	printf ("the: occurs %d times\n", count_the );
	printf ("and: occurs %d times\n", count_and );
	return 0;
}

