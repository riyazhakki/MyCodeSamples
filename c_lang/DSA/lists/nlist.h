/* nlist.h: uniform list with non-chronological pair of links */

/* structures */

struct item {
	struct item *bigger;
	struct item *smaller;
	char data [1];
};

typedef struct LIST {
	struct item *smallest;
	struct item *biggest;
	struct item *transferred;
	int (*compare) (char *, char *);
	long magic;
	int size;
	int nitems;
	long ntrans;
	int dir;
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

# define Smallest		ld->smallest
# define Biggest		ld->biggest
# define Transferred	ld->transferred
# define Compare 		ld->compare
# define Magic			ld->magic
# define Size			ld->size
# define Nitems			ld->nitems
# define Ntrans			ld->ntrans
# define Dir			ld->dir
# define Transfer_flag	ld->transfer_flag
# define Bigger			item->bigger
# define Smaller		item->smaller
# define Data			item->data

/* useful macros */

# define list_empty(ld)		!Nitems
# define ntransaction(ld)	Ntrans
# define reset_transferred(ld) Transferred = NULL

/* procedure templates */

LIST * open_list (int size, int (*compare)());
int close_list (LIST *ld );
int insert_in_list (LIST *ld, char *data );
int read_smallest (LIST *ld, char *data );
int read_biggest (LIST *ld, char *data );
int read_bigger (LIST *ld, char *data );
int read_smaller (LIST *ld, char *data );
int delete (LIST *ld);

