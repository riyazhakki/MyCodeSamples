/* Accept a string and do: 	Rprint (src, dst, count)
				Lprint (src, dst, count)
				printm (src, dst, count, positon)  
				xcopy (src, dst, count, position, offset)*/

# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# define MAX 50 
# define MID_RIGHT 1
# define MID_LEFT 2
# define OUTPUT printf ("Output: %s\n\n", dptr)

// function prototypes
void read_input (char *src, int *cnt);
void Rprint ( char sptr[], char dptr[], int count);
void Lprint ( char sptr[], char dptr[], int count);
void printm ( char sptr[], char dptr[], int count, int pos);
void xcopy ( char sptr[], char dptr[], int count, int pos, int offset);
void reverse (char *str);
void display_menu (void);

main(){

	char src [MAX];
	char *dst;
	int count;
	int pos;
	int choice;
	
	display_menu();
	printf ("Enter the choice:");
	scanf ("%d", &choice);
	getchar();		 // bypass /n
	xcopy (src, dst, count, pos, choice);
}

void read_input (char *src, int *cnt){
	char c;
	int i = 0;

	printf ("Enter the string:");
	while (c = getchar()) {
		if ( c == '\n') 
			break;
		src[i++] = c;
	}
	    src [i] = '\0';

	printf ("Enter character count:");
	scanf ("%d", cnt);
	if (*cnt > strlen (src) / 2){
		printf ("count value must equal or less than half of string size..!\n");
		exit (1);
	}
}

void Rprint (char sptr[], char dptr[], int count){
	int i, j;

	dptr = (char *) malloc (strlen (sptr) + 1);
	for (i = strlen (sptr) - count, j = 0; sptr [i] != '\0'; )
		dptr [j++] = sptr [i++]; 			//copy string to dest 
	dptr [j] = '\0';
	OUTPUT;
}

void Lprint (char sptr[], char dptr[], int count){
	int i;

	dptr = (char *) malloc (strlen (sptr) + 1); // dynamic mem alloc
	for (i = 0; i < count; i++)
		dptr [i] = sptr [i]; 			//copy string to dest 
	dptr [i] = '\0';
	OUTPUT; 
} 

void printm (char sptr[], char dptr[], int count, int pos){
	int i, j;
	dptr = (char *) malloc (strlen (sptr) + 1); // dynamic mem alloc
	switch (pos){
		case MID_RIGHT :
			for ( i = strlen (sptr) / 2, j =0; j < count && sptr[i] != '\0';)
				dptr [j++] = sptr [i++];
			dptr [j] = '\0';
			break;

		default : printf ("Invalid input....!\n");
				break;

		case MID_LEFT :
			for (i = strlen (sptr) / 2, j = 0; j < count && i >= 0;) 
				dptr [j++] = sptr [i--]; 			//copy string to dest 
			dptr [j] = '\0';
			reverse (dptr);
			break;
	}
	OUTPUT;
}

void reverse (char *str){
	int i, j;
	char temp;

	for (i =0, j = strlen (str) - 1; i < j; i++, j--)
		temp = str [i], str [i] = str [j], str [j] = temp;
}

void xcopy ( char src[], char dst[], int count, int pos, int offset){
	switch (offset){
		case 1 	:	read_input (src, &count);
					Rprint (src, dst, count);
					break;
		case 2 : 	read_input (src, &count);
					Lprint (src, dst, count);
					break;
		case 3 :	read_input (src, &count);
					printf ("Enter the position (>>:1 <<:2 :)");
					scanf ("%d", &pos);
					printm (src, dst, count, pos);
					break;
		case 4 :	printf ("Good bye....\n");
					exit (0);
		default:	printf ("Invalid input.....!\n");
		}
}

void display_menu (void){
		printf ("***************< MENU >***************\n");
		printf ("1. Rprint (src, dst, count);\n");
		printf ("2. Lprint (src, dst, count);\n");
		printf ("3. printm (src, dst, count, position);\n");
		printf ("4. Exit\n");
		printf ("**************************************\n");
}	
