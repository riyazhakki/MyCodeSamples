# include <stdio.h>
# define MAX 6 
main(){
	int i, j, k, sum = 0;

	for (i = 1; i < MAX; i++){

		for ( k = MAX; k > i; k--)  // prints left spaces
			printf(" ");
		
		sum += 1;
		
		if ( i > 1 ){
			printf ( "%d", 1 );
			
			for (j = 2; j < i; j++){
				if ( j != 2 && ( j - 1 == (( i - 1 ) / 2))){
						printf ( " %d",  i + 1 );
				}
				else
				printf ( " %d", i - 1 );
			}
			
			printf ( " 1" );
			printf ( "\n" );
		}
		else{
			printf ( "1" );
			printf ( "\n" );
		}
	}

}

