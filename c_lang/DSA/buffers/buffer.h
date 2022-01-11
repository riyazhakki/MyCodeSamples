
// buffer.h:


typedef struct {
	char * write;
	char * read;
	char * end;
	int nbytes;
	int nchars;
	char beg[1];
}BUFFER;

// procedures

BUFFER * create_buf ( int nbytes );
int write_buf ( BUFFER *bd, char data );
char read_buf ( BUFFER *bd );
void destroy_buf ( BUFFER * bd );

// macros

#define buf_empty(bd) (!(bd->nchars))
#define buf_full(bd) (bd->nchars == bd->nbytes)

// symbolic literals

# define BUF_SUCCESS 	0
# define BUF_FAIL 		NULL
# define BUF_FULL	 	-1
# define BUF_EMPTY		-2
