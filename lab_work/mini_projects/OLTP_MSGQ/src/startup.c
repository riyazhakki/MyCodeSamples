# include <stdio.h> 
# include <stdlib.h>
# include <unistd.h>

main () {
	switch ( fork () ){
		case -1: fprintf ( stderr, "Child not ceated...\n" );
					exit ( 1 );

		case 0: execl ( "server", "server", "NULL" );
				printf ("SERVER NOT CREATED...\n" );

	}
}
