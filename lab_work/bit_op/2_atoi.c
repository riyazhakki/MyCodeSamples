/* 2.  ASCII to integer conversion.	*/

# include <stdio.h>
# include <stdlib.h>

main () {
	char str[10];
	int i;

	printf ("Enter the a string of numbers:");
	scanf ("%s", str);
	i = my_atoi (str);
	printf ("Entered value is: %d\n", i);
}

int my_atoi (char *s) {
	int i = 0;
	while (*s) {
		if (*s >= '0' && *s <= '9') {
			i = (i << 3) + (i << 1) + (*s - '0');
			//i = 10 * i + (*s - '0');  //Alternate without bit oper.
			s++; 
		}
		else {
			fprintf (stderr, "Not a valid Integer string...!\n");
			s++;
			exit (1);
		}
	}
	return i;
}
