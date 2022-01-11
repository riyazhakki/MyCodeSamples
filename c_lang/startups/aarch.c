# include <stdio.h>
main(){
	char ch;
	int i, j, k, blank = -1;

	for( i = 0; i < 7; i++){
		ch = 64;
		for (j = 0; j < 7 - i; j++)
			printf ("%c ", ++ch);
		
		if (j >= 7 - i){
			for (k = 0; k < blank  ; k++)	// print blank space		
				printf ("  "); 

			for (j = 0; j < 7 - i; j++){
				if (i == 0 && ch == 'G'){
					ch --;
					j++;
				}
				printf ("%c ", ch--);
			}
		}
		printf ("\n");
		blank += 2;
	}
}

