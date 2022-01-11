/* Write a program to add two numbers */
# include <stdio.h>

main ()
{
	/* Declare the local variables */
	int a, b, c;

	/* scan the input from key board */
	printf ("Enter the value of a & b:");
	scanf ("%d %d", &a, &b);

	/* calculation parts */
	c = a + b;

	/* result part */
	printf ("The sum of the two numbers is %d\n", c);
}
