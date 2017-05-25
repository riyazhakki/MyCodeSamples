# include <stdio.h>
//# include <termcap.h>

main ( ) {

	//printf ("\033[7m" );  // inverse 
	printf ("\n\n\n\n");
	printf ("\033[5m" );  // blinking
	printf ("\033#3 \tUttaratians\n" );	 //double tops
	printf ("\033[5m" );  // blinking
	printf ("\033#4 \tUttaratians\n" );	 // double bottoms
	printf ("\033[0m" );	// normal

	printf ("\033#6 \t\tRocks...\n" );		//single

	printf ("\033[0m\n" );
}
