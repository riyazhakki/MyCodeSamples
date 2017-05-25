/* ex03_myshell.c : Read standard input lines 
				Seperate the line into words to form a sentance 
				Assume no special character processing  

   ex07_myshell.c :	Modify this to handle I/O redirections:
   				> file		< file		>> file		  */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>

# define MAX 40

main ( int argc, char * argv [ ] ) {
	char line [MAX];
	char **word = NULL;
	char *p, *item, save;
	int nwords, i;
	int fd;

	int redir_lt_flag, redir_gt_flag, redir_file_out, redir_file_in;
	int redir_gtgt_flag;
	redir_lt_flag = redir_gt_flag = redir_file_in = redir_file_out = 0;
	redir_gtgt_flag = 0;

	printf ("My_Shell_MRH>");
	while ((fgets(line, MAX, stdin)) ){
		p = line;
		nwords = 0;
		while (1){

			while (*p == ' ' || *p == '\t' || *p == '\n')  p++;
												//Skip WSpaces
			item = p;
			if(!*p)  break;			// exit on EOL

			while ( *p != ' ' && *p != '\t' && *p != '\n') {

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
		}
		word = realloc (word , ++nwords * sizeof (char *));
		word [nwords - 1] = NULL;

		switch ( fork () ) {
			case -1 : 	fprintf (stderr, "Can't forked...!\n");
						exit (1);

			case  0 : 
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

					   	execvp ( *word, word );
				  	   	printf ("Invalid command....!\n");
						exit (4);
						break;
		}
		redir_lt_flag = redir_gt_flag = redir_gtgt_flag = 0;
		wait (NULL);
		printf ("My_Shell_MRH>");
	}
	exit (0);
}
	
