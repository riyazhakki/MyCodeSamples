/* Write a program that reads standard input and prints the 
	characters greater than 40 */

# include <stdio.h>

main(){
	char ch;

	printf("To exit press ctrl + d\n");
	while ( (ch = getc (stdin)) != EOF){
		if (ch > 40 )
			putc (ch, stdout);
	}
}
