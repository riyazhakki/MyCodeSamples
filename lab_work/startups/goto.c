/* simple program to deomonstrate goto statement */
# include <stdlib.h>
//# include <string.h>
# include <stdio.h>
main(){
//	char s[10];
	char *s;

	printf( "Enter a word:" );
	scanf ( "%s", s);

	if ( strcmp ("hello",s) == 0 )
		goto lable;

	printf ( " \"goto\" statement is not executed\n" );
	exit (0);
	lable: printf ( " \"goto\" statement is executed\n" );
	exit(0);
}
