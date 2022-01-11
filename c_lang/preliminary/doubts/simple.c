# include <stdio.h>

main (){
	int i;
	char c;
	scanf ("%d", &i);
	printf ("i=%d\n", i);
	while (c = getchar ()){
	if ( c == '\n' )
		break;
	printf ("while");
	}
}
	
