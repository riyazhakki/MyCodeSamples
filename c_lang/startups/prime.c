/* Program to find the given number is prime or not */
# include <stdio.h>
main(){
	int inp, i = 2, prime = 1;
	printf( "Enter the Number to find it's prime:" );
	scanf( "%d", &inp ) ;
	while( i < inp ) {
		if ( ( inp % i ) == 0 ){
			prime = 0;
			break;
		}
	  i++;
	}
	if( prime )
		printf( "Given number is a prime\n" );
	else
		printf( "Given number is not a prime\n" );
	
}
