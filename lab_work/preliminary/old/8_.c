/* Read standard input and print the number of occurences of characters
int graphic format. a:...  */

# include <stdio.h>
# define MAX 50 

main(){

	char c;  				// read each character
	char input [MAX];		// store each character in array
	int count [MAX];		// count for corresponding character 
	int size = 0;			// size of string
	int i, j;				// temporaries
	int largest = 0;
	
	printf ("For exit ctrl + d \n");
	printf ("Enter a string (max 50 characters):\n");
	
	while ( (c = getchar())!= EOF){		// read character till EOF

		for ( i = 0; i <= size; i++){
			if ( c == input[i] ){		// if within array
				count [i]++;
				i++;
				break;
			}
		}

		if ( c != input [i - 1] ){	
			input [i - 1] = c;			// store in array
			count [i - 1] = 1;
			size++;
		}
	}
	size--;

	//find largest
	for ( i = 0; i < size; i++)
		if (largest < count [i] )
			largest = count [i];
	
	for (; largest != 0; largest--){
		for ( i = 0; i < size; i++){
			if ( count [i] == largest)
				putchar ('.');
			else
				putchar (' ');
		}
		putchar ('\n');
	}
}
