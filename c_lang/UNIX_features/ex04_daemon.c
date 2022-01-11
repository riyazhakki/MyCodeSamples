# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

main ( ) {
	switch ( fork () ) {

		case -1 : fprintf ( stderr, "Can't forked...\n" );
						break;	

		case 0	: setpgrp(); 
					close(0); close(1); close (2); 
					while (1) { };
					break;

		default	  : printf (" parent exiting... \n" );
					exit (0);
	}
}
