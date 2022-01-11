/* ex52_slist.h: singly linked list with chronological pair of links */

/* structures */

struct item {
	struct item *next;
	char data [1];
};

typedef struct LIST {
	struct item *first;
	struct item *last;
	struct item *transferred;
	long magic;
	int size;
	int nitems;
	long ntrans;
	int transfer_flag;
}LIST;

# define FORWARD	0
# define REVERSE	1

/* symbolic literals for return values */

# define L_SUCCESS	0
# define L_EMPTY	1
# define L_NO_MORE	2
# define L_ILLEGAL 	3
# define L_NOT_READ	4
# define L_FAIL		NULL

/* symbolic literals for member acess: TO IMPROVE CLARITY */

# define First			ld->first
# define Last			ld->last
# define Transferred	ld->transferred
# define Magic			ld->magic
# define Size			ld->size
# define Nitems			ld->nitems
# define Ntrans			ld->ntrans
# define Transfer_flag	ld->transfer_flag
# define Next			item->next
# define Data			item->data

/* useful macros */

# define list_empty(ld)		!Nitems
# define ntransaction(ld)	Ntrans
# define reset_transferred(ld) Transferred = NULL

/* procedure templates */

LIST * open_list (int size);
int close_list (LIST *ld );
int append (LIST *ld, char *data );
int read_first (LIST *ld, char *data );
int read_middle ( register LIST *ld, char *data );
int read_last (LIST *ld, char *data );
int read_next (LIST *ld, char *data );
int delete (LIST *ld);

