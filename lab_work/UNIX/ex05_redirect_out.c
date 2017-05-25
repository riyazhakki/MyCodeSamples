/* ex05_redirect.c: 
	Write a program that executesthe flollwing commands as child processes:
			1> ls -l > temp
			2> wc < temp
			3> ls -l | wc		*/

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>

main ( ) {

int fd;
	
	switch ( fork( ) ) {
		case -1 : fprintf ( stderr, "Can't forked...!\n" );
					exit ( 1 );
		
		case 0 	: 
					fd = open ( "temp", O_CREAT | O_TRUNC | O_WRONLY, 0600 );
					if ( fd < 0 ) {
						fprintf ( stderr, "File can't create...\n");
						exit ( 2 );
					}
					close ( 1 );
					if ( dup ( fd ) != 1 ) {
						fprintf ( stderr, "Error in Dup...\n");
						exit ( 3 );
					}
					close ( fd );
					execl ("/bin/ls", "ls", "-l", NULL );
					fprintf ( stderr, "Can't exec ...!\n" );
					exit ( 4 );
	}
	wait ( NULL );
	exit ( 0 );
}
