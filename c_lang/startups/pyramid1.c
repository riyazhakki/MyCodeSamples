# include <stdio.h>
main(){
	int i, j, k, sum = 0;

	for (i = 0; i < 4; i++){
		
		for ( k = 4; k > i; k--)
			printf("    ");

		for (j = 0; j <= i; j++){
			sum += 1;
			printf ("       %d", sum);
		}
		printf ("\n");
	}
}

