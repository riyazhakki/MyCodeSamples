# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <unistd.h>

main ( ) {
	int pid;
	int fd;
	
	switch ( pid = fork () ) {

		case -1 : fprintf ( stderr, "Child not created...\n" );	
					exit ( 1 );

		case 0  :
					setpgrp ();
					execl ( "demon", "demon", "NULL" );
					break;

		default : 
			fd = open ( "filepid", O_CREAT | O_TRUNC | O_WRONLY , 0744 );
			if (fd < 0 ){
				fprintf ( stderr, "Error in file opening...\n" );
				exit (1);
			}
			write ( fd, &pid, sizeof (pid) );
			printf (" %d  written successfully...\n", pid );
			close ( fd );
			exit (0);

	}

}
