/* 3. Copy input to output, replacing  series of consecutive spaces by
		a single space.
	  Note: use int to hold getchar().
		use a flag to indicate the first space
			eccountered in a series of spaces.
		For next set of spaces, no output needed. 
		On non-space, reset the flag. */

# include <stdio.h>

main(){
	int c;
	int flag = 0;

	while ((c = getchar()) != EOF){
		if (c == ' '){
			if (!flag){
				flag = 1;
				putchar(c);	
			}
		}
		else{
			flag = 0;
			putchar(c);
		}
	}
}


		

