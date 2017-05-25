/* reverse_line2.c: A program to accept an input file and copy it to an output  file and copy it to an output file but last line first, last but one line second, and first line last.  */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

main ( int argc, char *argv [] ) {
	FILE *ifp, *ofp;
	int c;
	int pos, next_pos, temp_pos;

	if ( argc < 3 ) {
		fprintf ( stderr, "Usage: <a.out> <input_file> <output_file>\n");
		exit (1); 
	}
	ifp = fopen (argv [1], "r");
	if ( ifp == NULL ) {
		printf ( "%s file can't be open\n", argv [1] );
		exit (0);
	}
	ofp = fopen (argv [2], "w");
	if ( ofp == NULL ) {
		printf ( "%s file can't be open\n", argv [2] );
		exit (0);
	}

	fseek (ifp, 0, SEEK_END);
	pos = ftell ( ifp );
	while (  pos > 1 ) {
		while (1) {
			c = getc (ifp);			
			if (  c == '\n' || ftell ( ifp ) == 1 ) 
				break ;
			fseek (ifp, -2, SEEK_CUR);	
		}
		next_pos = ftell ( ifp );
		temp_pos = next_pos;
		while ( temp_pos != pos ) {
			c = getc (ifp);			
			putc ( c , ofp);
			temp_pos = ftell ( ifp );
		}
		pos = next_pos ;
		fseek ( ifp, pos - 2, SEEK_SET );
	}
}
