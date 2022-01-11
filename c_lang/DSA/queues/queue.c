/* queue.c : a rudimentary version precompiled to queue.o */

# include <stdio.h>
# include "queue.h"

char * malloc (int);
//int free (char *);
void *memcpy ( char *, char *, int );

QUEUE * openQ (int nmax, int size) {
	register QUEUE * qd;
	if (nmax < 1 || size < 1 )   // check for lemons
		return Q_FAIL;
	qd = (QUEUE *) malloc ( sizeof (*qd) + nmax * size - 1 );
									// adjust size for dynamic array
	if (qd == NULL) 	
		return Q_FAIL;
	
	qd->dp = qd->beg;
	qd->ep = qd->beg;
	qd->end = qd->beg + nmax * size;
	qd->nmax = nmax;
	qd->size = size;
	return qd;  /* return the handle */
}  

int enQ ( QUEUE * qd, char * item ) {
	if ( Qfull(qd) ) return Q_FULL;
	memcpy (qd->ep, item, qd->size );
	if (( qd->ep += qd->size ) >= qd->end )
		qd->ep = qd->beg;		// inc with wrap
	qd->nitems++;
	return Q_SUCCESS;
}

int deQ ( QUEUE * qd, char * item ) {
	if ( Qempty(qd) ) return Q_EMPTY;
	memcpy (item, qd->dp, qd->size);
	if (( qd->dp += qd->size ) >= qd->end ) 
		qd->dp = qd->beg;
	qd->nitems--;     // missing in class notes
	return Q_SUCCESS;
}

int closeQ ( QUEUE * qd ) {
	free (qd);
	return Q_SUCCESS;
}
