/* ex05_3.c: 
	Write a program that executesthe flollwing commands as child processes:
			1> ls -l > temp
			2> wc < temp
			3> ls -l | wc		replace a temp file with a pipe */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>

main ( ) {

int pfd [2];
	
	if ( pipe ( pfd ) < 0 ) {
		fprintf ( stderr, "Can't create piped...!\n" );
		exit ( -1 );
	}

	switch ( fork( ) ) {
		case -1 : fprintf ( stderr, "Can't forked...!\n" );
					exit ( 1 );
		
		case 0 	:	
					close ( 1 );   // colse stdout
					if ( dup ( pfd [ 1 ] ) != 1 ) { 
						//now value of fd [1] is copied in 1th place (stdout) in filetable
						fprintf ( stderr, "Error in Redirecting...\n");
						exit ( 3 );
					}
					// duplicated on stdout
					// now close copy of pipe in child
					close ( pfd [ 0 ] );
					close ( pfd [ 1 ] );

					execl ("/bin/ls", "ls", "-l", NULL );
					fprintf ( stderr, "Can't exec ...!\n" );
					exit ( 4 );
		default	:
					close ( 0 );  // close stdin
					if ( dup ( pfd [ 0 ] ) != 0 ) { 
						//now value of fd [0] is copied to 0th place (stdin) in filetable
						fprintf ( stderr, "Dup system fault...\n");
						exit ( 3 );
					}

					// duplicated on stdin
					// now close copy of pipe in parent 
					close ( pfd [ 0 ] );
					close ( pfd [ 1 ] );

					execl ("/usr/bin/wc", "wc", NULL );
					fprintf ( stderr, "Can't exec wc...!\n" );
					exit ( 4 );
	}
	exit ( 0 );
}
