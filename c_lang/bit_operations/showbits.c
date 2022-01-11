
# include <stdio.h>
# include <string.h>

void rev ( char * );

main ()
{
	int c, i = 0;
	char str [39];

	printf ("Enter a interger:");
	scanf ("%d", &c);

	while (c) {
		if ( c & 1 )
			str [i++] = '1';
		else 
			str [i++] = '0';
		c =	c>>1;
	}
	str[i] = '\0';
	rev (str);
	printf ("Bits: %s\n",str);
}

void  rev (char *s) {
	int i, j;	
	char t;
	for ( i = 0, j = strlen (s) - 1; i < j; i++, j-- ){
		t = s [i];
		s [i] = s [j];
		s [j] = t;

	}
}
