/* stack.c : the library module precompiled to stack.o */

# include <stdio.h>
# include "stack.h"

char * malloc ( int );
void *memcpy ( char *, char *, int );

STACK * open_stack ( int n, int size ) {
	register STACK * sd;	/* volatile box for eventual return */
	if ( n < 1 || size < 1 ) return S_FAIL;	/* check lemons */

	sd = ( STACK * ) malloc (sizeof * sd);	/* allocate handle */
	if ( sd == NULL ) return S_FAIL;

/*	sd->beg = malloc ( n * size );
	sd->sp = sd->beg;
	sd->end = sd->beg + n * size;
	sd->n = n;
	sd->size = size;
*/
	/* super efficient: substitute to above  5 statements */

	sd->end = (sd->sp = sd->beg = malloc ((sd->n = n) * (sd->size = size)))
					+ n * size;
	
	return sd;
}

int push ( register STACK * sd, char * item ) {
	if (stack_full ( sd )) return S_FULL ;
	memcpy ( sd->sp, item, sd->size );
	sd->sp += sd->size;
	return S_SUCCESS;
}

int pop ( register STACK * sd, char * item ) {
	if ( stack_empty ( sd ) ) return S_EMPTY;
	sd->sp -= sd->size;
	memcpy ( item, sd->sp, sd->size );
	return S_SUCCESS;
}

int close_stack ( STACK * sd ) {
	free ( sd->beg );
	free ( sd );
	return S_SUCCESS;
}

