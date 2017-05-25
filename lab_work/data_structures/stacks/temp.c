# include <stdio.h>

main () {

int arr [100];
int *ptr = arr;

arr [ 0 ] = 10 ;
arr [ 1 ] = 20 ;

printf ( "%d", *++arr );

}
