/* 1. Try printing the full range of escaped characters:
		\a \b \c ... \z
	with printf. Explain the sesult on the screen.
	Modify the program slightly to prove your theory.
	(For characters like: \b \r)	*/

# include <stdio.h>
main(){
		printf("\a");
		printf("\b");
		printf("\\c unknwon escap sequence\n ");
	 	 printf("\\n prints newline on screen ");

}
