
# include <stdio.h>

main ()
{
	char buf [50] = "hello";
	char data [50];
	setvbuf (stdin, buf, _IOFBF, 50);
	scanf ("%s", data );
	printf ( " data: %s \n", data );

}
