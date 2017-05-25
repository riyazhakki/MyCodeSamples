# include <stdio.h>
main () {

	int a,b,c;
	printf ("Enter a & b:");
	scanf ("%d%d", &a, &b);

	asm mov ax,a
	asm add ax,b
	asm mov c,ax

	printf ("%d", c);
}
