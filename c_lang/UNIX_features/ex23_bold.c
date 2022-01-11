# include <stdio.h>
//# include <termcap.h>

main ( ) {
	//printf ("\033[1m Hello\n" );  //bold
	//printf ("\033[0m Hello\n" );

	//printf ("\033[4m Hello\n" );  //underline
	//printf ("\033[0m Hello\n" );	// normal

	//printf ("\033[4m Hello\n" );  //underline
	printf ("\033[4;5m" );  // blinking
	printf ("\033#3 Riyaz\n" );	 //double tops
	printf ("\033#4 Riyaz\n" );	 // double bottoms
	printf ("\033[0m" );	// normal

	printf ("\033[7m" );  // inverse 
	printf ("\033[17m" );  // inverse 
	printf ("\033#6 Hakki\n" );		//single

	printf ("\033[0m\n" );
	printf ("\033[8;3!}^G\033[3;3!]}" );
}
