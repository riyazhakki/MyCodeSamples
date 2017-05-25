/* dsqueue_b.c : a rudimentary version precompiled to dsqueueb.o 
	queue on stretchable array 
	use dynamic structure 
	b) By returning the (possibly ) new key value in the enqueue
		procedure. The application will have to be changed to always
		strore return value into its qd when it calls enqueue. */

# include <stdio.h>
# include "dsqueue_b.h"

# define ROQ 1

char * malloc (int);
void *memcpy ( char *, char *, int );

int ep_old = 0, dp_old = 0;

QUEUE * openQ (int nmax, int size) {
	register QUEUE * qd;

	if (nmax < 1 || size < 1 )   // check for lemons
		return Q_FAIL;

	qd = (QUEUE *) malloc ( sizeof (*qd) + nmax * size - 1  );
	if (qd == NULL) 	
		return Q_FAIL;

	qd->dp = qd->beg;
	qd->ep = qd->beg;
	qd->end = qd->beg + nmax * size;
	qd->nmax = nmax;
	qd->size = size;

	return qd;  /* return the handle */
}  

QUEUE * enQ ( QUEUE *qd, char * item ) {
	char * src, * dst, *old_dp;
	if ( Qfull(qd) ){
		qd->nmax += ROQ;
		dp_old = (qd->dp - qd->beg);

		qd = (QUEUE *) realloc (qd, (sizeof(*qd) + qd->nmax * qd->size - 1));

		// reposition pointers
		src = (char *)qd->end;
		dst = qd->end = qd->beg + qd->nmax * qd->size;
		old_dp = qd->dp;

		printf ("Queue sratched....\n");
			while ( src >= old_dp ){
				memcpy ( dst, src, qd->size);
				dst -= qd->size; 
				src -= qd->size; 
			}
			dst += qd->size; 
			qd->dp = dst;

		printf ("Data moved...\n");

		qd->ep = qd->beg + ep_old;
	}

	memcpy (qd->ep, item, qd->size);

	if (( qd->ep += qd->size ) >= qd->end ) 
			qd->ep = qd->beg;		// inc with wrap
		
	ep_old = (qd->ep - qd->beg);
	qd->nitems++;
	return qd;
}

int deQ ( QUEUE * qd, char * item ) {
	if ( Qempty(qd) ) return Q_EMPTY;

	memcpy (item, qd->dp, qd->size);

	if (( qd->dp += qd->size ) >= qd->end )
		qd->dp = qd->beg;
	
	dp_old = (qd->dp - qd->beg);

	qd->nitems--;    
	return Q_SUCCESS;
}

int closeQ ( QUEUE * qd ) {
	free (qd);
	return Q_SUCCESS;
}
