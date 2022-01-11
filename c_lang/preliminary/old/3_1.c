/* Read standard input and print the number of occurences of characters
int graphic format. a:...  */

# include <stdio.h>
# define MAX 50 

main(){

	int frequency [MAX];	// frequency of corresponding input character 
	int char_count = 0;		// char_count of input 
	int i, j;				// temporaries
	char c;  				// read each character
	char input [MAX];		// store each character in array
	
	printf ("For exit ctrl + d \n");
	printf ("Enter a string (max 50 characters):\n");
	
	while ( (c = getchar())!= EOF){		// read character till EOF

		for (i = 0; i <= char_count; i++){
			if (c == input[i]){		// if within array
				frequency [i]++;
				i++;					// need if breaked
				break;
			}
		}

		i--;

		if (c != input [i]){	
			input [i] = c;			// store in array
			frequency [i] = 1;
			char_count++;
		}
	}
	
	for (i = 0; i < char_count; i++){		// display output
		printf ("%c : ", input [i]);
		for (j = 0; j < frequency [i]; j++)	
			printf (".");
		printf ("\n");
	}
}
