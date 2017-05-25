/* v6.c : one application that uses the stack library */

# include <stdio.h>
# include <stdlib.h>
# include "stack.h"

# define NITEMS 5 		/* retrain maintainablility */

char line [ 100 ];
STACK *sd;

main () {
	int num; 				/* for data transfer */
	register char * p;		/* walking pointer */

	sd = open_stack ( NITEMS, sizeof ( num ) );

	if ( sd == S_FAIL ) exit ( 1 );
	while (1) {
		printf (" Use E to exit; P to pop; Number to push: " );
		if (fgets ( line, 100, stdin ) == NULL )
			exit ( 2 );		/* User in a hurry & has typed eof */
		for ( p = line; *p == ' '|| *p == '\t'; p++ ); /*skip spaces */
		switch ( *p ) {
			case '0' : case '1': case '2': case '3' : case '4' :
			case '5' : case '6': case '7': case '8' : case '9' :
				/* a number has to be entered */
				if (stack_full (sd) ){
				printf ("STACK FULL...!\n");	
   				continue;  /* error */
				}
				num = atoi (p);
				push ( sd, (char * ) & num );
				break;
			case 'p': case 'P':		/* support both cases */
				if ( stack_empty (sd) ){
					printf ("STACK EMPTY...!\n");
					break;
				}
				pop ( sd, (char *) & num );
				printf ("%d\n", num );
				break;
			case 'e': case 'E': 			/* graceful exit */
				while (!stack_empty ( sd ) ) {
					pop (sd, (char *) & num );
					printf ("%d\n", num );
				}
				exit (0);
			}

		}
	}

