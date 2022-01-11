/* reverse_line2.c: A program to accept an input file and copy it to an output  file and copy it to an output file but last line first, last but one line second,... and first live last.  */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

main ( int argc, char *argv [] ) {
	FILE *ifp, *ofp;
	int c;
	int nchar = 0;
	int pos, next_pos, temp_pos;
	char *line = NULL;
	char *ptr;

/*	if ( argc < 3 ) {
		fprintf ( stderr, "Usage: <a.out> <input_file> <output_file>\n");
		exit (1); 
	}
	ifp = fopen (argv [1], "r");
	ofp = fopen (argv [2], "w");
*/	
//	ifp = fopen ("reverse_in.dat", "r");
	ifp = fopen ("uttara", "r");
	fseek (ifp, 0, SEEK_END);
	c = '\0';
	pos = ftell ( ifp );
	printf ("pos: %d \n", pos);
	while (  pos > 1 ) {
		while (1) {
			printf ("%d :", ftell(ifp));
			c = getc (ifp);				// read a char and move one byte forward
			putc ( c , stdout );
			if (  c == '\n' || ftell ( ifp ) == 1 ) 
				break ;
			printf (" -:inside backward_while:- \n"); 
			fseek (ifp, -2, SEEK_CUR);	// move 2 byte backwords
		}

		next_pos = ftell ( ifp );
		temp_pos = next_pos;
		printf ("middle : next_pos: %d\n", next_pos);

		while ( temp_pos != pos ) {
			c = getc (ifp);			
			putc ( c , stdout );
			temp_pos = ftell ( ifp );
			printf (" -:inside forward_while:- \n"); 
			printf ("temp_pos: %d\t pos: %d\n", temp_pos, pos);

			if ( feof ( ifp ) ) {
				printf ("\nEOF\n");
				break; 
			}
		}
		printf ("outside 2 innerwhile\n");
		pos = next_pos ;
		printf ("pos: %d \ttemp_pos: %d\n", pos, temp_pos);
		fseek ( ifp, pos - 2, SEEK_SET);
	}
}
