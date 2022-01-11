/***************************************************************************
15_insert_string.c:
	This should insert the source string inside the destination at the given 
postion. the characters at and beyond the position in the destination string 
must be moved right. Assume destination has enough memory.
***************************************************************************/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define MAX 30

void insert_string ( char *, char *, int );

main () {
	char dst [ MAX ];

	strcpy ( dst, "the wrong son" );
	insert_string ( dst, "per", 10 );
	printf ("%s\n", dst );
}

void insert_string ( char *dst, char *src, int pos ) {
	int i;
	int total_len = 0;
	int src_len = 0;
	char *scratch;

	if ( pos > strlen (dst) ) {
		fprintf (stderr, "Invalid position...\n");
		exit ( 1 );
	}
	
	total_len = (strlen (dst) + strlen (src ));
	src_len = strlen (src);

	scratch = malloc ( total_len + 1 );
	strcpy ( scratch, dst + pos );
	strcpy ( dst + pos, src );
	strcat ( dst, scratch );
	free ( scratch );
}
