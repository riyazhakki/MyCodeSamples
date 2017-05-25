# include <stdio.h>
main(){
	int i, j, k, sum = 0;

	for (i = 0; i < 4; i++){
		
		for ( k = 4; k > i; k--)
			printf("    ");
		
		sum += 1;

		for (j = 0; j <= i; j++){
			printf ("     %d  ", sum);
		}
		
		printf ("\n");
	}
}

