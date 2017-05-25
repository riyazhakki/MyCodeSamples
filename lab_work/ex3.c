# include <stdio.h>

# define RESET 0
# define SET   1

main ( ) {

	int c;
	int space_flag = RESET;

	while ( ( c = getchar ( ) ) != EOF ) {
		if ( space_flag == RESET && c == ' ' ) {
			space_flag = SET;
			putchar ( c );
		} else if ( space_flag  == SET && c == ' ' ) {
			continue;
		}
		else{
			putchar ( c );
			space_flag = RESET;
		}
			
	}

}
