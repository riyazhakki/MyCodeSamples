/* 15. NOTE: use cc -v --hlep x.c
	on LINUX to look at cc(1) options.
	Study the options.
*/

# include <stdio.h>

main(){
	struct x{
		char c;
		int i;
	} abc;
	printf ("%u %u\n", &abc.c, &abc.i);
	printf ("Size of struct is %d\n", sizeof (abc));
}

