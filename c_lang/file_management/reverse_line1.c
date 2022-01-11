/* reverse_line1.c: A program to accept an input file and copy it to an output file and copy it to an output file but last line first, last but one line second,... and first live last.  */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

main ( int argc, char *argv [] ) {
	FILE *ifp, *ofp;
	int c;
	int nchar = 0;
	char *line = NULL;
	char *ptr;

	if ( argc < 3 ) {
		fprintf ( stderr, "Usage: <a.out> <input_file> <output_file>\n");
		exit (1); 
	}
	ifp = fopen (argv [1], "r");
	ofp = fopen (argv [2], "w");
	fseek (ifp, 0, SEEK_END);

	while (ftell(ifp) != 1) {		// till begining of a file
		fseek (ifp, -2, SEEK_CUR);	// move 2 byte backwords
		c = getc (ifp);				// read a char and move one byte forward
		line = realloc (line, ++nchar * sizeof (c)); // stretchable array
		if (c == '\n') {
			line [ nchar - 1 ] = '\0';
			ptr = line;
			ptr = ptr + strlen (line);		// move ptr to end of line
			while (ptr-- != line) 			// till ptr reaches to beg of line
				putc ( *ptr, ofp);   // output char by char
			putc ('\n', ofp);
			free (line);		// otherwise memory leak
			line = NULL;
			nchar = 0;
		}
		else
			line [ nchar - 1 ] = c;		// store a char to a line array
	}
	fclose (ifp);
	fclose (ofp);

}
