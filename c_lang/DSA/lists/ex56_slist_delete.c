/* ex56_slist_delete.c : delete object in linked list */

# include <stdio.h>
# include <string.h>
# include "ex56_slist.h"

# define L_MAGIC (((long)'L'<<24) || ((long)'I' <<16) || \
					((long)'S' <<8) || ((long) 'T'))
				// some way of generating a unique signature

char * malloc (int);
//int free (char *);

LIST * open_list (int size, int (*compare)() ) {
	register LIST * ld; /* volatile box with standardized name */
	
	if (size < 1 || !compare) return L_FAIL;
	ld = (LIST *) malloc (sizeof(LIST));
	Compare = *compare;
	First = NULL;
	Last = NULL;
	Transferred = NULL;
	Nitems = 0;
	Ntrans = 0;
	Size = size;
	Magic = L_MAGIC;
	Transfer_flag = 0;
	return ld;
}

int close_list (register LIST *ld ) {
	register struct item *item;
	register struct item *p;

	if (Magic != L_MAGIC ) return L_ILLEGAL;

	for (item = First; item;) {
		p = item;
		free (p);
		item = p->next;
	}

	free (ld); 
	return L_SUCCESS;
}

int append ( register LIST * ld, char * data ){
	register struct item * item;

	if (Magic != L_MAGIC ) return L_ILLEGAL;
	item = (struct item *) malloc (sizeof * item + Size - 1);
	Ntrans++;
	Nitems++;
	Next = NULL;
	memcpy (Data, data, Size);
	if (Last){
		Last->next = item;
		Last = Last->next;		
	}
	else
		Last = First = item;
	return L_SUCCESS;
}

int read_first ( register LIST *ld,  char * data ) {
	if (Magic != L_MAGIC ) return L_ILLEGAL;
	if (!Nitems) return L_EMPTY;
	Transferred = First;
	memcpy (data, Transferred->data, Size);
	Ntrans++;
	Transfer_flag = 1;
	return L_SUCCESS;
}

int accessN (register LIST *ld, int num, char * data ){
	int i;
	for ( i = 0, Transferred = First; i < Nitems - num + 1; 
								i++,Transferred = Transferred->next )
	memcpy (data, Transferred->data, Size);
	Ntrans++;
	Transfer_flag = 1;
	return L_SUCCESS;
}

int read_last ( register LIST *ld,  char * data ) {
	if (Magic != L_MAGIC ) return L_ILLEGAL;
	if (!Nitems) return L_EMPTY;
	Transferred = Last;
	memcpy (data, Transferred->data, Size);
	Ntrans++;
	Transfer_flag = 1;
	return L_SUCCESS;
}
	
int read_next ( register LIST *ld,  char * data ) {
	if (Magic != L_MAGIC ) return L_ILLEGAL;
	if (!Nitems) return L_EMPTY;
	if (!Transferred) Transferred = First;
	else if (!Transferred->next) return L_NO_MORE;
	else Transferred = Transferred->next;
	memcpy (data, Transferred->data, Size);
	Ntrans++;
	Transfer_flag = 1;
	return L_SUCCESS;
}

int delete (register LIST *ld, char *data) {
	register struct item *item;
	register struct item *prev;
	register struct item *p;

	if (Magic != L_MAGIC ) return L_ILLEGAL;

	for (p = First; p; )
		if ((*Compare)(data,p->data) == 0){ 
			if (p == First ) {
				First = p->next; 
				free (p);
			}
			else {
				prev->next = p->next; 
				free (p);
			}
			Nitems--; Ntrans++;
			return L_SUCCESS;
		}
		else{
			prev = p; 
			p = p->next;
		}

	return L_ILLEGAL;
}
