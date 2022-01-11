#include <stdio.h>
main(){
	int a, b, c, res;
	printf ( "Enter Three Values:" );
	scanf ( " %d %d %d ", &a, &b, &c );
	res = ( a > b ) && ( a > c ) ? a : ( b > c ) ? b : c;
	printf( " greater value is %d ", res);
}
