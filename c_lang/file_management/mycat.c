/* Program similar to cat(1) */

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>

void read_stdin ();
void display_file ( int, char * );
void reset_flags();

int verbose, line_no, end_line, begin, filename_on = 1;
int file_count = 0;
int cnt = 1;
char filename [30][10];

main ( int argc, char *argv[] ) {
	int fd;
	int i, j;

	verbose =  line_no = end_line = 0; 
	begin = 1; 

	if (argc < 2)
		read_stdin();
	else {
			for  ( i = 1;  i < argc; i++ ) {
				if  ( argv[i][0] == '-' ) {
					if ( argv[i][1] == '\0' ) 
						read_stdin();
					else {
						for ( j = 1; argv [i][j] !=  '\0';  j++) {
							switch (argv [i][j]) {
								case 'v' :  verbose = 1; 
										break;
								case 'n' :  line_no = 1;
										break;
								case 'e' :  end_line = 1;
										break;
							}
						} // end of for j
					}
					if ( argv [i + 1] == NULL ) {
						read_stdin();
					}
				}
				
				else if (argv [i] != NULL ){
						++file_count;
						filename_on = 1;
						strcpy (filename[file_count -1], argv[i]);
				}
		} //end of for i

			for ( i = 0; i < file_count; i++ ) {

					fd = open (filename [i], O_RDONLY, 0);
					if ( fd  < 0 ){
						printf ( "Can't  open a file %s\n", filename[i]);
						exit (1);
					}
					display_file (fd, filename [i]);
					close (fd);
			}
	}
}

void display_file (int fd, char filename []) {
	# define BSIZE 1
	char buf [BSIZE];
	int n;
	begin = 1;

	if (filename_on) 
	while ( (n = read ( fd, buf, BSIZE ) ) > 0 ) {
		if ( line_no && (*buf == '\n' || begin)){
			if ( begin ) {
				printf ( "%8d   ", cnt++ );
				begin = 0;
			}
			if ( *buf == '\n' )
				begin = 1;
		}
		if ( verbose && *buf < ' ' && *buf != '\n') {
			putchar ('^');
			putchar (*buf + 0x40);
		}
		if ( end_line && *buf == '\n')
			putchar ('$');
		putchar (*buf);
	}
	putchar ('\n');
}

void read_stdin () {
	int c;
	int fd;
	char filename[20];

	printf ("Press 'Ctrl+d'\n");
	sprintf (filename, "file%d", getpid());
	fd = open (filename, O_WRONLY | O_CREAT, 0755);
	if ( fd < 0) {
		printf ("File can't open....\n");
		exit (1);
	}
	while ( ( c = getchar ()) != EOF) 
		write ( fd, &c, 1 );
	close (fd);
	display_file (open (filename, O_RDONLY) , "Keyboard");
	close (fd);
}
