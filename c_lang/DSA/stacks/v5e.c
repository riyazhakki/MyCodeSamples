/*****************************************************************************
v5d.c: Stack on stretchable array.

	realloc: better done in chunksof ROQ.
	Keep track of current size of the array in addition to the current 
	stack pointer.
	Better to use a stack that grows downwards.

*****************************************************************************/

# include <stdio.h>
# include <stdlib.h>
	
# define LENGTH 50
# define ROQ 03

int *sp = NULL;
int *start =  NULL;
int *tmp_ptr;
char line [ LENGTH ];
char *p;
int size = ROQ;

main ( ) {

	start = ( int * ) malloc ( ROQ * sizeof ( int ) ); 
	sp = start + ROQ - 1;

	while ( 1 ) {
		if ( sp < start ) { 				// STACK FULL
			printf ("Stack full...!\n");
			printf ("Stack will be streached.\n");
			printf ( "<num> to push; p to pop; e to exit: ");
			
			size += ROQ;
			start = ( int * ) realloc ( start, (size + 1)   * sizeof ( int ) );

			// Data move
			sp = start + size - 1;
			tmp_ptr = start + ( size - ROQ ) - 1;
			while ( tmp_ptr >= start ){		
				*sp = *tmp_ptr;
				 sp--; tmp_ptr--;
			}
		}
		else if ( sp == start + size - 1 )						// STACK EMPTY
			printf ( "<num> to push; e to exit: ");
		else
			printf ( "<num> to push; p to pop; e to exit: ");

		if ( !fgets ( line, LENGTH, stdin ) )
			exit ( 1 );

		for ( p = line; *p == ' ' || *p == '\t'; p++ );  // skip white spaces

		switch ( *p ) {
			default: continue;
			case '\n': continue;
			case '0': case '1': case '2': case '3': 
			case '4': case '5': case '6': case '7': 
			case '8': case '9': 
				*sp = atoi ( p );		// PUSH
				sp--;
			continue;
			case 'p': case 'P':			// POP
				if ( sp >= (start + size - 1 )  ) 
					printf ("Stack underflow...!\n");
				else {
					sp++;
					printf ( "%d\n",  *sp );	
				}
					continue;

			case 'e' : case 'E':
				if ( sp <= (start + size - 2 ) ) {
					printf ( "You forgot to pop \n" );
					while ( sp <= (start + size - 2 ) ){
						sp++;
						printf ( "%d\n", *sp  );
					}
				}
				printf ("bye bye\n" );
				exit ( 0 );
		}
	}
}
