/***************************************************************************
14_insert_string.c:
	This should insert the source string inside the destination at the given 
postion. the characters at and beyond the position in the destination string 
must be moved right. Assume destination has enough memory.
***************************************************************************/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

void insert_string ( char *, char *, int );

main () {
	char dst [ 40 ];

	strcpy ( dst, "the wrong son" );
	insert_string ( dst, "per", 10 );
	printf ("%s\n", dst );
}

void insert_string ( char *dst, char *src, int pos ) {
	char save [ 20 ];
	char *save_ptr;
	char *dst_pos;
	int n;
	int i;
	
	save_ptr = save; // for walking in save 

	for ( i = 0; i < pos; i++, dst++ ) 
		if ( *dst == '\0' ) {
			fprintf ( stderr, "Position is out of bound\n");
			exit (1);
		}
	
	dst_pos = dst; 		// preserve dst's current position
	while ( *save_ptr++ = *dst++ ); // save string of beyond position 
	while ( *dst_pos++ = *src++ );	// join src to dst string.
	dst = --dst_pos; 			// point to '\0'
	save_ptr = save;
	while ( *dst++ = *save_ptr++ ); // join saved string to dst string.
}
