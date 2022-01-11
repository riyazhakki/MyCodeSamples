/* squeue.h :  include for queue applications */

/* structure definitions */

typedef struct {
	int nmax;   /*maximum number of items in queue */
	int size; 	/* size of an item in the uniform queue */
	int nitems; /* current number of items in queue */
	char *beg;
	char *dp;
	char *ep;
	char *end;
}QUEUE;

/* procedure templates  */

QUEUE * openQ ( int nmax, int size );
int enQ ( QUEUE * qd, char * item ); 
int deQ ( QUEUE * qd, char * item ); 
int closeQ ( QUEUE * qd );

/* macros for high speed */

# define Qfull(qd) ( qd->nitems == qd->nmax )
# define Qempty(qd) ( qd->nitems == 0 )

/* symbolic literals to improve documentation */

# define Q_SUCCESS 0
# define Q_FAIL 	NULL
# define Q_FULL		-1
# define Q_EMPTY	-2

/* Note that Q_FAIL has been defined as NULL since it is the 
	return value of the procedure openQ that returns a pointer */
