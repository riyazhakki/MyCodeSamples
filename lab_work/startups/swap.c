/* Program to swap two numbers using call by value */

# include <stdio.h>
main(){
	int a,b;

	void swapbyval (int, int);
	void swapbyref (int *, int *);

	printf ("Enter the value for a:");
	scanf ("%d", &a);
	printf ("b:");
	scanf ("%d", &b);
	swapbyval (a, b);
	printf ("Values after swapbyval(): a: %d b: %d\n", a, b);
	swapbyref (&a, &b);
	printf ("Values after swapbyref(): a: %d b: %d\n", a, b);
}

void swapbyval (int a, int b){
	int temp;
	temp = a;
	a = b;
	b = temp;
}

void swapbyref (int *a, int *b){
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
