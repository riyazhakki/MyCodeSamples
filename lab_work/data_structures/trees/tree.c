/* tree.c : 
	Layered version of binary ordered treee
		Modules : tree.c tree.h
		Application : nums.c
*/
# include <stdio.h>
# include "tree.h"

# define T_MAGIC 	3786

char * malloc (int);
char * memcpy (char *, char *, int);

TREE * open_tree ( int size, int (*compare)() ){
	register TREE *td;

	if (size < 1 || !compare ) return T_FAIL;
	td = (TREE *) malloc (sizeof (TREE));
	Root = NULL;
	Size = size;
	Compare = compare;
	Nitems = Ntrans = 0;
	Magic = T_MAGIC;

	return td;
}


int nleaves ( TREE *td ) {
	return how_many (Root);
}

int how_many (register struct node * node ) {
	if (!node) {
	return 0;
	}
	if (!Left){
	return 1;
	}
	return how_many (Left) + how_many (Right);
}

void navigate ( TREE *td, void (*action)(), void * app_data ) {
	if (!Root) return;
	traverse ( Root, action, app_data );
}

void traverse ( struct node *node, void (*action)(), void *app_data ) {
	if (!node) return;  
	if (!Left) 
		(*action) (Data, app_data); // place_leaf (Data, td );
	else{
		traverse ( Left, action, app_data );
		traverse ( Right, action, app_data );
	}
}

int add_leaf ( TREE *td, char * new ){
	int n;
	int counter = 0;
	void place_leaf (char *, void *);

	n = how_many(Root);
	n++;
	Array = (char *)malloc ( n * Size );
	Pos = Array;
	New_added = 0;
	New = new; // new data

	traverse ( Root, place_leaf, (void *)td );

	if (!New_added ) memcpy (Pos, new , Size);
//	free_tree (Root);
	Root = array_to_tree (Array, Size, n, &counter);

	free (Array);
	return T_SUCCESS;
}

void place_leaf (char *old, void *x ){

	register TREE *td = (TREE *) x;

	if (!New_added && (*Compare) (New, old) < 0 ) {
		memcpy (Pos, New, Size);
		Pos += Size;
		New_added = 1;
	}
	memcpy (Pos, old, Size);
	Pos += Size;
}

struct node * array_to_tree ( char *array, int size, int n, int *pcounter ) {

	register struct node *node;
	int nleft;

	node = (struct node*) malloc (sizeof * node + size - 1);
	if ( n == 1 ) {
		memcpy (Data, array, size);
		Left = Right = NULL;
		return node;
	}
	nleft = n/2;

	// n&1=> odd number

	if ( (n & 1) && ( ++*pcounter & 1))
		nleft ++;
	
	Left = array_to_tree (array, size, nleft, pcounter);
	Right = array_to_tree (array + nleft * size, size, n -nleft, pcounter);

	/* copy structural data */
	memcpy (Data, array + (nleft-1) * size, size);
	return node;
}

int read_first (register TREE *td, char *data){
	register struct node *node;

	for (Path = 0, Height = 0, node = Root; Left; Height++) 
			node = Left;

	memcpy (data, Data, Size);
	return T_SUCCESS;
}

int read_next (register TREE *td, char *data){
	register struct node *node;
	int x;
	int mask;

	if (++Path & (1<<Height)){
		Path--;
		return T_NO_MORE;
	}

	for ( x = Height, node = Root, mask = 1<<(Height -1); x; x--) {
		if(!Left) break;
		if ( Path & mask )
			node = Right;
		else 
			node = Left;
		mask >>= 1;
	}

	if (x) {
		while (x--){
			Path |= mask;
			mask >>= 1;
		}
	}
	else while (Left) {
		Height++;
		Path <<=1;
		node = Left;
	}
	memcpy (data, Data, Size);
	return T_SUCCESS;
}
