
/* aqueue.c : Layered version of assorted queue on array 
	Modules : aqueue.c aqueue.h
	Application : assorted.c
	uses cut piece data movement */

# include <stdio.h>
# include "aqueue.h"

# define Head aqd->head
# define Tail aqd->tail
# define Beg aqd->beg
# define End aqd->end
# define Nfree aqd->nfree
# define Nitems aqd->nitems

char * malloc (int);
void *memcpy ( char *, char *, int );

AQUEUE * openQa ( int nbytes ) {
	register AQUEUE * aqd;
	if (nbytes < 1 )   // check for lemons
		return AQ_FAIL;

	aqd = (AQUEUE *) malloc ( sizeof (*aqd) + nbytes );
									// adjust size for dynamic array
	if (aqd == NULL) 	
		return AQ_FAIL;
	
	aqd->head 	= aqd->beg;
	aqd->tail 	= aqd->beg;
	aqd->end 	= aqd->beg + nbytes;
	aqd->nbytes	= nbytes;
	aqd->nfree	= nbytes;
	aqd->nitems	= 0;
	return aqd;  /* return the handle */
}  

int enQa ( register AQUEUE * aqd, char *data, int size ) {
	register int cut_piece;

	if (size < 1 || size > 255 ) return AQ_TOO_BIG;				
	if ((size + 1) > Nfree ) return AQ_NO_SPACE;
	Nitems++;
	Nfree -= size + 1;

	*Tail++ = (unsigned char) size; // enQa size

	if (Tail >= End ) Tail = Beg;	// wraparound
	if (size >= (End - Tail)) {   	// if data not fit, cut_piece
		cut_piece = End - Tail;
		memcpy (Tail, data, cut_piece );		// enQ data
		Tail = Beg; 				// wraparound & store cut_piece
		size -= cut_piece;
		data += cut_piece;
	}
	if (size) {
		memcpy (Tail, data, size);		// enQ data
		Tail += size;
	}

	return AQ_SUCCESS;
}

int deQa ( register AQUEUE * aqd, char * data) {
	register int cut_piece;
	int size;

	if ( !Nitems ) return AQ_EMPTY;

	Nitems--;
	size = (unsigned char) *Head++;
	Nfree += size + 1;
	if (Head >= End ) Head = Beg;
	if (size >= (End - Head )) {
		cut_piece = End - Head;
		memcpy (data, Head, cut_piece);
		Head = Beg;
		data += cut_piece; 
		size -= cut_piece;
	}
	if (size) {
		memcpy (data, Head, size );
		Head += size;
	}
	return AQ_SUCCESS;
}

void display (union data *data) {
	if ( data->type == SHORT)
		printf ("%d\n", data->Short.value); 
	else if ( data->type == LONG )
		printf ("%ld\n", data->Long.value); 
	else if ( data->type == DOUBLE)
		printf ("%f\n", data->Double.value); 
}

int closeQa ( AQUEUE * aqd ) {
	free (aqd);
	return AQ_SUCCESS;
}
