/* program to demonstrate macro */

# include <stdio.h>

//# define max( x, y ) x > y ? x : y
# define prtcdsqr( x ) ( x ) * ( x )
# define unprtcdsqr( x )  x  *  x 

main(){
	int x, y, z;

//	printf ( "Enter two values:");
//	scanf ( "%d %d", &x, &y );
//	z = max ( x, y ) + 10;
//	printf ( "max ( %d, %d ): %d\n", x, y, max ( x, y) );
	printf ( "Enter the value to find square:");
	scanf ( "%d", &x);
	z = unprtcdsqr ( x + 2 ); // this treat as x + 2 * x + 2 which is wrong 
	printf ( "unprtcdsqr ( %d + 2 ): %d\n", x, z); 
	z = unprtcdsqr1 ( x + 2 ) * 2; 
	                 // this treat as (x + 2) * (x + 2) which is wrong 
	printf ( "prtcdsqr ( %d + 2 ): %d\n", x, z); 
}
