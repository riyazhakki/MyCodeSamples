/*****************************************************************************
v5d.c: Stack on stretchable array.

	realloc: better done in chunksof ROQ.
	Keep track of current size of the array in addition to the current 
	stack pointer.
	Better to use a stack that grows upwards.

*****************************************************************************/

# include <stdio.h>
# include <stdlib.h>
	
# define LENGTH 50
# define ROQ 03

int *sp = NULL;
int *start =  NULL;
char line [ LENGTH ];
char *p;
int size;

main ( ) {
	size = ROQ;
	start = ( int * ) malloc ( size * sizeof ( int ) ); 
	sp = start ;
	while ( 1 ) {
		if ( sp  > start + size - 1 ) { 
			printf ("Stack full...!\n");
			printf ("stack will be streached.\n");
			size += ROQ;
			start = ( int * ) realloc ( start, size * sizeof ( int ) );
			sp = start + size - ROQ;
			printf ( "<num> to push; p to pop; e to exit: ");
		}
		else if ( sp <= start)						// STACK EMPTY
			printf ( "<num> to push; e to exit: ");
		else
			printf ( "<num> to push; p to pop; e to exit: ");

		if ( !fgets ( line, LENGTH, stdin ) )
			exit ( 1 );

		// SKIP WHITE SPACES
		for ( p = line; *p == ' ' || *p == '\t'; p++ );

		switch ( *p ) {
			default: continue;
			case '\n': continue;
			case '0': case '1': case '2': case '3': 
			case '4': case '5': case '6': case '7': 
			case '8': case '9': 
				*sp = atoi ( p );		// PUSH
				sp++;
			continue;
			case 'p': case 'P':
				if ( sp <= start ) 
					printf ("Stack underflow...!\n");
				else{ 
					--sp;
					printf ( "%d\n",  *sp );		// POP
				}
				continue;
			case 'e' : case 'E':
					if ( sp > start ) {
						printf ( "You forgot to pop \n" );
						while ( sp > start ){
							--sp;
							printf ( "%d\n", *sp  );
						}
					}
					printf ("bye bye\n" );
					exit ( 0 );
		}
	}
}
