# include <stdio.h>
# include <stdlib.h>

main(int argc, char **argv){

	int num1 = atoi ( argv[1] );
	int num2 = atoi ( argv[3] );

	printf (":%d", num1 % num2);

}
