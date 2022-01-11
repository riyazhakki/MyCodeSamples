/* aqueue.h:  Layered version of assorted queue on array 
	Modules : aqueue.c aqueue.h
	Application : assorted.c
	uses cut piece data movement
*/

typedef struct {
	char * head;
	char * tail;
	char * end;
	int nbytes;
	int nfree;
	int nitems;
	char beg[1];
}AQUEUE;

struct Short {
	unsigned char type;
	short value;
};
struct Long{
	unsigned char type;
	long value;
};
struct Double{
	unsigned char type;
	double value;
};
union data{
	unsigned char type;
	struct Short Short;
	struct Long Long;
	struct Double Double;
};
// procedures
AQUEUE * openQa ( int nbytes );
int enQa ( AQUEUE *adq, char * data, int size );
int deQa ( AQUEUE *adq, char * data );
void display (union data *data);
int closeQa (AQUEUE * aqd);

// macros

#define Qempty(aqd) (!(aqd->nitems))
#define Qfull(aqd) ((size + 1) > aqd->nfree)

// symbolic literals
# define AQ_SUCCESS 	0
# define AQ_FAIL 		NULL
# define AQ_FULL	 	-1
# define AQ_EMPTY		-2
# define AQ_TOO_BIG 	-3
# define AQ_NO_SPACE 	-4


# define SHORT 	1
# define LONG 	2 
# define DOUBLE 3 

