# include <stdio.h>
# include <stdlib.h>


main(){
	char **str;
	
	str = (char **) malloc (sizeof (char*)); 
	*str = (char *) malloc (10 * sizeof (char)); 

	scanf("%s",str[0]);
    printf("%s", str[0]);
}

