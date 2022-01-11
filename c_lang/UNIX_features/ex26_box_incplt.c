# include <stdio.h> 
main () {
	printf ("\033[9a");// 9spaces
	printf ("text\n");
	printf ("\033[4i");
	printf ("text\n");
	printf ("\033[m");
}
