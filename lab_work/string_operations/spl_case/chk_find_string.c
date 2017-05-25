/*****************************************************************************
find_string.c:
	check if the entire string at s is a sub-string of the string at r.
******************************************************************************/

# include <stdio.h>

# define TRUE	1
# define FALSE	0

int find_string ( char *, char * );

main ( ) {
	char *str = "chatter_box"; 	char *substr = "hat";

//	char *str = "how are you"; char *substr = "owl";

	if (find_string (str, substr))
		printf ("substring %s found in string %s\n", substr, str);
	else
		printf ("substring not found\n");

}

int find_string ( char * r, char * s ) {
	char *t;
	int i;

	while (*r) {
		t = s;
		printf ("while1: r: %c = t: %c\n", *r, *t );
		i = 0;
		while ( *r++ == *t++ ){
			printf ("\twhile2: r: %c = t: %c\n", *r, *t );
//			r++; t++;
			i++;
		}

	if ( *t == '\0' )
		return TRUE;

		r -= i;
		r++;
	}
	return FALSE;
}
