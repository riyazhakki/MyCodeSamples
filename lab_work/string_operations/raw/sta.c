
# include <stdio.h>
void fun ();

main () {
//static int var = 5;

//printf ("%d", var--);
//if (var)
//	main();

fun();
fun();
fun();

}

void fun ()
{
	static int i = 0;
	printf ("%d", i++);

}
