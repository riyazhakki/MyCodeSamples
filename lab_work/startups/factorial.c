/* Program to find factorial of a given number */

#include <stdio.h>
main(){
	int fact = 1, inp, i = 1;
	printf("Enter the number for factoral:");
	scanf("%d",&inp);
	while(i <= inp){
		fact = fact * i;
		i++;
		}
	printf("Factorial of %d is %d",inp,fact);
	}

