/*****************************************************************************
find_string.c:
	check if the entire string at s is a sub-string of the string at r.
******************************************************************************/

# include <stdio.h>

# define TRUE	1
# define FALSE	0

int find_string ( char *, char * );

main ( ) {
	//char *str = "chatter_box"; 	char *substr = "hat";

	char *str = "how are you"; char *substr = "owl";

	if (find_string (str, substr))
		printf ("substring %s found in string %s\n", substr, str);
	else
		printf ("substring not found\n");

}

int find_string ( char * r, char * s ) {
	char *t;
	int i;

	while (*r) {
		t = s; i = 0;
		while ( *r == *t ){
			r++; t++; i++;
		}

		if ( !*t )
			return TRUE;
		r -= i; r++;
	}
	return FALSE;
}
