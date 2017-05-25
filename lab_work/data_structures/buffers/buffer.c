/* buffer.c: Layered version of circular buffer
Modules : buffer.c buffer.h
Application: fifo.c */

# include <stdio.h>
# include "buffer.h"

# define Write 	bd->write
# define Read 	bd->read
# define Beg 	bd->beg
# define End 	bd->end
# define Nchars bd->nchars
# define Nbytes bd->nbytes

char * malloc (int);

BUFFER * create_buf ( int nbytes ) {
	register BUFFER * bd;

	if (nbytes < 1 )   // check for lemons
		return BUF_FAIL;

	bd = (BUFFER *) malloc ( sizeof (*bd) + nbytes );
									// adjust size for dynamic array
	if (bd == NULL) 	
		return BUF_FAIL;
	
	bd->write	= bd->beg;
	bd->read	= bd->beg;
	bd->end 	= bd->beg + nbytes;
	bd->nbytes	= nbytes;
	bd->nchars	= 0;
	return bd;  /* return the handle */
}  

int write_buf ( register BUFFER * bd, char data ) {
	if ( Nchars == Nbytes ) return BUF_FULL;
	*Write++ = data;
	if ( Write >= End ) Write = Beg;

	Nchars ++;

	return BUF_SUCCESS;
}

char read_buf ( register BUFFER * bd ) {
	char data;

	if ( !Nchars )	return BUF_EMPTY;
	data = *Read++;

	Nchars --;
	if ( Read >= End ) Write = Beg;

	return data;
}

void destroy_buf ( BUFFER * bd ) {
	free (bd);
}
