/****************************************************************************
convert_vowels.c:
	Convert all vowels in input stream to upper case. (assign2.c)
****************************************************************************/

# include <stdio.h>

main ( ) {
	int c;

	while ( ( c = getchar ( ) ) != EOF ) {
		switch ( c ) {
			case 'a' : 
			case 'e' : 
			case 'i' : 				
			case 'o' : 
			case 'u' : printf ( "%c", c - 32 ); 
			 break;
			default :	printf ( "%c", c );
		}
	}
}
