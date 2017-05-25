/*****************************************************************************
v5c.c:
	A simple stack of integers on an array. 
	Pre Dec Store as push operation;
	stack grows downwards.

*****************************************************************************/

# include <stdio.h>
# include <stdlib.h>
	
# define LENGTH 50
# define NMAX 	05

int stack [ NMAX ];
int sp;
char line [ LENGTH ];
char *p;

main ( ) {

	sp = NMAX;
	while ( 1 ) {
		if ( !sp )
			printf ( "p to pop; e to exit: ");
		else if ( sp == NMAX )
			printf ( "<num> to push; e to exit: ");
		else
			printf ( "<num> to push; p to pop; e to exit: ");

		if ( !fgets ( line, LENGTH, stdin ) )
			exit ( 1 );

		for ( p = line; *p == ' ' || *p == '\t'; p++ );

		switch ( *p ) {
			default: continue;
			case '\n': continue;
			case '0': case '1': case '2': case '3': 
			case '4': case '5': case '6': case '7': 
			case '8': case '9': 

				if ( !sp ) 
					printf ("Stack full...!\n");
				else
					stack [ --sp ] = atoi ( p );		//push
				continue;
			case 'p': case 'P':
				if ( sp == NMAX ) 
					printf ("Stack underflow...!\n");
				else 
					printf ( "%d\n", stack [ sp++ ] );		//pop
					continue;

			case 'e' : case 'E':
					if ( sp != NMAX ) {
						printf ( "You forgot to pop \n" );
						while ( sp != NMAX )
							printf ( "%d\n", stack [ sp++ ] );
					}
					printf ( "bye bye\n" );
					exit ( 0 );
		}
	}
}
