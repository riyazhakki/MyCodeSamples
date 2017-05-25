/* ex03_myshell.c : Read standard input lines 
				Seperate the line into words to form a sentance 
				Assume no special character processing  

   ex07_myshell.c :	Modify this to handle I/O redirections:
   				> file		< file		>> file		  

   ex10_myshell.c :	Modify this to handle simple shell script 

   ex10_minishell.c :	Modify this to support
   		1> I/O Redirection
		2> piping
		3> sequential processing
		4> conditional processing &&
		5> conditional processing ||						*/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

# define MAX 40

char line [MAX];
char **word = NULL;
char *p, *item, save;
int nwords, i;
int fd;
int status;
int redir_lt_flag, redir_gt_flag, redir_file_out, redir_file_in;
int redir_gtgt_flag;
int pipe_flag;
int pipe_file_in;
int pipe_file_out;

int pipe_0;
int pipe_1;
int v;

int wait_st;

int pfd [ 2 ];
struct stat st_buf;
FILE *rc;

void create_child ( void );
void create_cmd_list ( char * line );
void redirection ( void );
int script_file ( void );

main ( int argc, char * argv [ ] ) {

	printf ("My_Shell_MRH>");

	while ((fgets(line, MAX, stdin)) ){

		create_cmd_list ( line );

		if ( script_file ( ) ) {
			continue;
		}

		if ( word[0] != NULL && !pipe_flag ) {
			create_child ();
		}

		if ( pipe_flag ) {

			word [ pipe_file_out ] = NULL;
			v = 1;
			create_child ();

			strcpy ( word [ pipe_file_out - 1 ], word [pipe_file_out + 1] );
			v = 0;
			create_child ();

			close ( pfd [ 0 ] );
			close ( pfd [ 1 ] );

			pipe_flag = 0;
		}

		redir_lt_flag = redir_gt_flag = redir_gtgt_flag = 0;

		printf ("My_Shell_MRH>");
		while ( wait ( &wait_st ) != -1 );
	}
}

void create_child ( ) {
	switch ( fork () ) {
			case -1 : 	fprintf (stderr, "Can't forked...!\n");
						exit (1);

			case  0 :
						if ( pipe_flag ) {
								close (v);
								if ( dup (pfd [ v ] ) != v ) {
									fprintf ( stderr, "Error in piping...!\n");
									exit ( 2 );
								}
								close ( pfd [ 0 ] );
								close ( pfd [ 1 ] );
						}
					
						redirection ( );
					   	execvp ( *word, word );
				  	   	printf ("Invalid command....!\n");
						exit (4);
						break;
			 	break;
		} // EOSwitch
}

void create_cmd_list ( char * line ) {

		p = line;
		nwords = 0;
		while (1){ 
			while (*p == ' ' || *p == '\t' || *p == '\n')  p++;
												//Skip WSpaces
			item = p;
			if(!*p)  break;			// exit on EOL

			while ( *p != ' ' && *p != '\t' && *p != '\n') {

				if ( *p == '|' ) {
					pipe_flag = 1;
					pipe_file_out = nwords;
					pipe_file_in = nwords + 2;

					if ( pipe ( pfd ) < 0 ) {
						fprintf ( stderr, "Can't create pipe...\n" );
						exit ( -1 );
					}
				}

				if ( *p == '<' ) {
					p++;
					redir_lt_flag = 1;
					redir_file_in = nwords;

					while (*p == ' ' || *p == '\t' || *p == '\n')  p++;
					item = p;
				}

				if ( *p == '>' ) {
					p++;
					redir_gt_flag = 1;
					redir_file_out = nwords;

					if ( *p == '>' ){
						redir_gt_flag = 0;
						redir_gtgt_flag = 1;
						p++;
					}
					
					while (*p == ' ' || *p == '\t' || *p == '\n')  p++;
					item = p;
				}
				p++;  // Walk all chars till hit WSpace
			}

			save = *p;  *p = '\0';

			word = realloc (word , ++nwords * sizeof (char *));
			word [nwords - 1] = strdup (item);
			*p = save;
		} // line scan completed EOWhile(1)

		word = realloc (word , ++nwords * sizeof (char *));
		word [nwords - 1] = NULL;
}

void redirection ( ) {

	if ( redir_lt_flag ) {
		fd = open ( word [ redir_file_in ] , O_RDONLY ); 
		if ( fd < 0 ) {
			fprintf ( stderr, " file can't opened...!\n" );
			exit ( 1 );
		}

		close ( 0 );
		if ( dup ( fd ) != 0 ) {
			fprintf ( stderr, "Dup failiure...!\n" );
			exit ( 2 );
		}
		word [ redir_file_in ] = NULL;
	}

	if ( redir_gt_flag ) {
		if ( !redir_file_out ) {
			fprintf ( stderr, "Output file missing...!\n");
			exit ( 3 );
		}
		
		fd = open ( word [ redir_file_out ], O_CREAT 
							| O_TRUNC | O_WRONLY, 0600 );

		if ( fd < 0 ) {
			fprintf ( stderr, "gt: File can't create...\n");
			exit ( 2 );
		}

		close ( 1 );
		if ( dup ( fd ) != 1 ) {
			fprintf ( stderr, "Error in Dup...\n");
			exit ( 3 );
		}
		close ( fd );

		word [ redir_file_out ] = NULL;
	}
	
	if ( redir_gtgt_flag ) {
		if ( !redir_file_out ) {
			fprintf ( stderr, "Output file missing...!\n");
			exit ( 3 );
		}
				
		fd = open ( word [ redir_file_out ], O_APPEND 												| O_CREAT | O_WRONLY, 0600 );

		if ( fd < 0 ) {
			fprintf ( stderr, "gt: File can't create...\n");
			exit ( 2 );
		}

		close ( 1 );
		if ( dup ( fd ) != 1 ) {
			fprintf ( stderr, "Error in Dup...\n");
			exit ( 3 );
		}
		close ( fd );
		word [ redir_file_out ] = NULL;
	}
}

int script_file ( ) {

		status = stat ( word [0], &st_buf );

		if ( ( status != -1 ) && (st_buf.st_mode & S_IFMT ) == S_IFREG ) {


			if ( (st_buf.st_mode & S_IXOTH) == S_IXOTH){
				rc = fopen ( word [ 0 ] , "r" );
				if ( fd < 0 ) {
					fprintf ( stderr, "Can't open %s file... \n" );
					exit ( 1 );
				}

				while ((fgets(line, MAX, rc )) ){
					if ( line [ 0 ] == '#' )
						continue;
					create_cmd_list ( line );
					create_child ( );
					wait (0);
				}
			}
		printf ("My_Shell_MRH>");
		return 1;
		}
	return 0;
}
