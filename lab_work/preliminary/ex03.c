/* Read standard input and print the number of occurences of characters
int graphic format. a:...  */

# include <stdio.h>
# define MAX 26 

main(){

	int count [MAX];		// char_count of input 
	int i, j;				// temporaries
	char c;  				// read each character
	
	//initialization

	for (i = 0; i < 26; i++)
		count [i] = 0;

	printf ("For exit ctrl + d \n");
	printf ("Enter a string (max 50 characters):\n");
	
	while ( (c = getchar())!= EOF){		// read character till EOF
		if (c >= 'a' && c <= 'z')
			count [c - 'a']++;
		if (c >= 'A' && c <= 'Z')
			count [c - 'A']++;
		}

	//Display Output

	for (i = 0; i < 26; i++){
		if (count [i] > 0){
			printf ("%c:",('a'+ i));
			for (j = 0; j < count [i]; j++)
				putchar ('.');
			putchar ('\n');
			}
		}
}
