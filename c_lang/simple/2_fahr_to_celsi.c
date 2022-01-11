/*	Write a program to convert 300, 290, 280, ... 0 degrees 
	Fahrenheit to Celsius. */

# include <stdio.h>

# define UPPER 300
# define LOWER 0
# define STEP 10

main(){
	int fehr;

	for (fehr = LOWER; fehr <= UPPER; fehr += STEP)
		printf ("%3d%6d\n", fehr, (5 * (fehr - 32) / 9));
}
