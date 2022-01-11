/* structure definitions */

typedef struct {
	char *beg;
	char *sp;
	char *end;
	int n;
	int size;
} STACK;

/* procedure templates */

STACK * open_stack ( int size );
int push (STACK * sd, char *item);
int pop (STACK * sd, char * item );
int close_stack ( STACK * sd );

/* macro for high speed */

# define stack_full(sd) (sd->sp == sd->end)
# define stack_empty(sd) (sd->sp == sd->beg)

/* symbolic literals to improve documentation */

# define S_SUCCESS 	0
# define S_FAIL		NULL
# define S_FULL 	-1
# define S_EMPTY	-2	


