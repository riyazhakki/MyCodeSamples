# include <stdio.h>

int square (a)
int a;{
	return (a*a);
}

main(){
	int a;

	printf ("Enter the value to find square:");
	scanf ("%d", &a);
	printf ("Squre of %d is %d\n", a, square(a));
}

