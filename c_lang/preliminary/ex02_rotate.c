
/* Rotate any array by (say) 2 places
	Ex: initial : array[] = {0, 1, 2, 3, 4};
		final	: 3, 4, 0, 1, 2 
*/

# include <stdio.h>
# include <stdlib.h>
# define MAX 5

main(){
	
	int array[MAX] = {0, 1, 2, 3, 4};
	int i, inp,n;

	//size of array
	n = sizeof (array) / sizeof (int);
	
	// read choice
	printf ("Rotate array by places:");
	scanf ("%d", &inp);

	//input validation
	if (inp < 0 || inp >n){
		fprintf ( stderr, "input range < 0 - 5 > only...\n");
		exit (1);
	}

	//print array
	for (i = 0; i < MAX; i++)
		printf ("%d, ", array [(n + i - inp) % n]); //index rotation

	printf ("\n");
}
