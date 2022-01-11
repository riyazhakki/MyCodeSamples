# include <stdio.h>
main(){
	int a = 10, b = 20;
	
	printf ("Initial values a : %d b : %d \n", a, b);

	if (a ++  || b ++ )
		printf ("a : %d b : %d \n", a, b);
		
	if (a == 10  && b ++ )
		printf ("a : %d b : %d \n", a, b);

	printf ("After All if a : %d b : %d \n", a, b);
}
