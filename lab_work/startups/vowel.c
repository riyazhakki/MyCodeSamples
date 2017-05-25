/* Program to find given character is vowel or not */

# include <stdio.h>
main(){
	char inp;

	printf ( "Enter a character:");
	scanf ( "%c", &inp);

	switch ( inp ){
		case 'a': //no break
		case 'i': //no break
		case 'o': //no break
		case 'u': //no break
		case 'v': printf( "Entered character is an vowel" );
					break;
		default: printf(" Entered character is a consonant" );
	}
}
