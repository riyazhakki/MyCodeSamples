
/* tree.h : 
	Layered version of binary ordered treee
		Modules : tree.c tree.h
		Application : nums.c
*/

/* structures */

struct node {
	struct node *left;
	struct node *right;
	char data [1];
};

typedef struct {
	struct node * root;
	long magic;
	int size;
	int nitems;
	long ntrans;
	int leaf_added;
	char *pos;
	int (*compare)();
	char *array;
	char *new;
	int new_added;
	int height;
	unsigned long path;

}TREE;

/* symbolic literals for return values */
# define T_SUCCESS	0
# define T_EMPTY	1
# define T_NO_MORE	2
# define T_ILLEGAL	3
# define T_NOT_READ	4
# define T_FAIL		NULL

/* symbolic literals for member access */
# define Root 		td->root
# define Magic		td->magic
# define Nitems		td->nitems
# define Ntrans		td->ntrans
# define Pos		td->pos
# define Size		td->size
# define Compare	td->compare
# define Array		td->array
# define New		td->new
# define New_added	td->new_added
# define Left		node->left
# define Right		node->right
# define Data		node->data
# define Height		td->height
# define Path		td->path

/* macro */
# define tree_empty(td)	!Nitems

/* procedure prototypes */

TREE * open_tree ( int size, int (*compare)() );
void navigate ( TREE *td, void (*action)(), void *app_data );
void traverse ( struct node *node, void (*action)(), void *app_data );
int nleaves ( TREE *td );
int how_many (struct node * node );
int add_leaf ( TREE *td, char *new );
void place_leaf (char *old, void *x );
struct node * array_to_tree ( char *array, int size, int n, int *pcounter );
int read_first (register TREE *td, char *data );
int read_next (register TREE *td, char *data );

