/* stacka.c : the library module precompiled to stack.o */
// stack on strechable array

# include <stdio.h>
# include "stacka.h"

# define ROQ 3

char * malloc ( int );
void *memcpy ( char *, char *, int );

STACK * open_stack ( int size ) {
	register STACK * sd;	/* volatile box for eventual return */
	int n = ROQ;
	if ( n < 1 || size < 1 ) return S_FAIL;	/* check lemons */
	sd = ( STACK * ) malloc (sizeof * sd);	/* allocate handle */
	if ( sd == NULL ) return S_FAIL;
/*
	sd->beg = malloc ( n * size );
	sd->sp = sd->beg;
	sd->n = n;
	sd->end = sd->beg + n * size;
	sd->size = size;
*/
	/* super efficient */

	sd->end = ( sd->sp = sd->beg = 
			malloc ( ( sd->n = n) * ( sd->size = size ) ) ) 
			+ n * size;

	return sd;
}

int push ( register STACK * sd, char * item ) {
	if (stack_full ( sd )){
		printf ("STACK FULL AND WILL BE STREACHED...\n");
		sd->n += ROQ;
		sd->beg = ( char * ) realloc ( sd->beg, sd->n * sd->size );	
		sd->end = sd->beg + (sd->n ) * sd->size;
	}
	
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

