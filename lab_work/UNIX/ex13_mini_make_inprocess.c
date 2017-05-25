/* mini_make.c: Program to perfrom make functionalities */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

char **file;
short nfiles;

void cmd_line_analysis ( int argc, char * argv [] );
void print_filenames ( );
void read_file ( char *fname );
void make ( char * target );

main ( int argc, char * argv[]) { 
	cmd_line_analysis ( argc, argv );
	print_filenames ( );
	make (file[0]);
}

void cmd_line_analysis ( int argc, char * argv [] ){

	int i, j;

	file = NULL;
	nfiles = 0;

	if ( argc > 1 ) {
		for ( i = 0; argv [ i ] != NULL; i++ ){
			for ( j = 0; argv [ i ] [ j ] != '\0'; j++ ) {
				if ( argv [ i ] [ j ] == '-' && argv [ i ] [ j+1 ] == 'f' ) {
					if ( strlen(argv [ i ]) > 2 ) {
						file = (char **)realloc(file,++nfiles * sizeof(char *));
						file [ nfiles - 1 ] = strdup (*(argv+i)+2);
					}
					else{
						if ( argv [ i + 1 ] == NULL ){
							fprintf ( stderr, "filename not found...!\n" );
							exit (2);
						}
						else{
							file = 
							(char **)realloc(file,++nfiles * sizeof(char *));
							file [ nfiles - 1 ] = strdup (argv [i+1] );
						}
					}
				}
			}
		}
	}

	else {
		file = ( char ** ) malloc ( ++nfiles );
		file [ nfiles - 1 ] = strdup ("makefile");
	}
}

void print_filenames ( ) {
	int i;
	printf ("%d Filenames \n", nfiles );
	for ( i = 0; i < nfiles; i++ ){
		printf ("%s\n", file [ i ] );
	}
}

void read_file (char *fname) {
	FILE *fp;
	int c;

	if ( (fp = fopen ( fname, "r" ) ) == NULL ){
		fprintf ( stderr, "Error in file opening...!");
		exit (1);
	}

	while ( ( c = getc ( fp )) != EOF ) {
		putchar ( c );
	}
}


void make ( char * target) {
	char cmd[20] = "cc -c ";

	strcat ( cmd, target );
	system ( cmd );
}
