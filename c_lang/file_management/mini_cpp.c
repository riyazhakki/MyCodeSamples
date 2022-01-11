/********************************************************
mini_cpp.c: A preprocessor that only handles
		# include <filename>
	directive Usage: a.out <input_file> <output_file>  
Note: Nested includes are to be supported.
**********************************************************/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define MAX_SIZE 1025

void in_to_out ( FILE *, FILE * );
int file_included ( char * ); 
int search ( char * , char **, int ); 
char tempfname [ 40 ];

main ( int argc, char * argv [ ] ) {
	FILE *ifp, *ofp;

	if ( argc < 3 ) {
		fprintf ( stderr, "usage: a.out <input_file> <output_file>");
		exit ( 1 );
	}
	ifp = fopen ( argv [1], "r" );
	ofp = fopen ( argv [2], "w" );

	in_to_out ( ifp, ofp );

	fclose ( ifp );
	fclose ( ofp );
}

void in_to_out ( FILE *ifp, FILE *ofp ) {
	FILE *ifp1;
	char line [ MAX_SIZE ];
	char *linep;
	int state;
	char filename [ 40 ];
	char *filenamep;

	filenamep = filename;

	enum  states { NORMAL, HASH, I, N , C, L, U, D, E, LT, QUOTE};

	state = NORMAL;

	while ( ( fgets ( line, MAX_SIZE, ifp ) ) != NULL ) {
		linep = line;
		while ( *linep != '\n' ) { 
			//printf ("%c", *linep );
			putc ( *linep, ofp );
			switch ( state ) {
				case NORMAL: 
					if ( *linep == '#' )
						state = HASH;
					else 
						state = NORMAL;
					break; 
				case HASH: 
					if ( *linep == 'i' )
						state = I;
					else if ( *linep != ' ' ) {
						state = NORMAL;
					}
					break;
				case I: 
					if ( *linep == 'n' )
						state = N;
					else
						state = NORMAL;
					break;
				case N: 
					if ( *linep == 'c' )
						state = C;
					else
						state = NORMAL;
					break;
				case C: 
					if ( *linep == 'l' )
						state = L;
					else
						state = NORMAL;
					break;
				case L: 
					if ( *linep == 'u' )
						state = U;
					else
						state = NORMAL;
					break;
				case U: 
					if ( *linep == 'd' )
						state = D;
					else
						state = NORMAL;
					break;
				case D: 
					if ( *linep == 'e' )
						state = E;
					else
						state = NORMAL;
					break;
				case E: 
					if ( *linep == '<' ){ 
						state = LT;
						}
					else if ( *linep == '"' )
						state = QUOTE;
					else if ( *linep != ' ' )
						state = NORMAL;
					break;
				case LT:
					if ( *linep == '>' ) {
						*filenamep = '\0';
						strcpy (tempfname, filename);
						filenamep = filename;
						sprintf ( filename, "/usr/include/%s", tempfname);
						if ( ! file_included ( filename) ) {
							if ( ( ifp1 = fopen ( filename, "r" ) ) == NULL) {
					fprintf (stderr, "%s std file can't open \n", filename );
								state = NORMAL;
								continue;
							}
						in_to_out (ifp1, ofp);
						}
						state = NORMAL;
					}
					else 
						*filenamep++ = *linep;
					break;
				case QUOTE:
				//printf ("QUOTE: %c", *linep );
					if (  *linep == '"' ) {
						*filenamep = '\0';
						if ( ! file_included ( filename ) ) {
							if ( ( ifp1 = fopen ( filename, "r" ) ) == NULL) {
							fprintf (stderr, "%s our file can't open \n", filename);
								state = NORMAL;
								continue;
							}
							in_to_out (ifp1, ofp);
						}
						state = NORMAL;
					}
					else 
						*filenamep++ = *linep;
					break;
				}
			linep++;
		}	
		putc ( '\n', ofp );
	}
}

int file_included ( char *fname ) {
	static char **file_list = NULL;
	static int nfiles = 0;
	int i;
	
	if ( search ( fname, file_list, nfiles ) )
		return 1;

	file_list = realloc ( file_list, ++nfiles * sizeof ( char * ) );
	file_list [ nfiles - 1 ] = strdup ( fname );

	return 0;
}

int search ( char * name, char * list [ ], int n) {
	int i;

	for ( i = 0; i < n; i++ ) 
		if ( strcmp ( list [ i ], name ) == 0 ) 
			return 1;

	return 0;
}
