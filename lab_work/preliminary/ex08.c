/* Read standard input and print the number of occurences of characters
int graphic format. 
  .
. . 
. . .
a b c  */

# include <stdio.h>
# define MAX 26 

main(){

	int count [MAX];				// char_count of input 
	int i, j;						// temporaries
	int largest = 0;
	char c;  						// read each character
	
										//initialization
	for (i = 0; i < 26; i++)
		count [i] = 0;

										//display message
	printf ("For exit ctrl + d \n");
	printf ("Enter a string (max 50 characters):\n");

										// read character till EOF
	while ( (c = getchar())!= EOF){		
	if (c >= 'a' && c <= 'z')
			count [c - 'a']++;
		if (c >= 'A' && c <= 'Z')
			count [c - 'A']++;
	}

										// find largest
	for (i = 0; i < 26; i++)
		if (largest < count [i])
			largest = count [i];

										// Display Output
	for (i = largest; i > 0; i--){
		for (j = 0; j < 26; j++){
			if (count [j] == 0)
				continue; 
			if (count [j] >= i)
				putchar('.');
			else
				putchar (' ');
		}
		putchar ('\n');
	}

	for (i = 0; i < 26; i++){
		if (count[i] == 0 )
			continue;
		putchar ('a' + i);
	}
	putchar ('\n');
}


