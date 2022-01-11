/* Accept decimal no. from stdin and convert it to hex;
	verify by printf.. %x. (atoh)	*/

# include <stdio.h>
# include <string.h>

# define MAX 20

void reverse (char [] );

main (){
	int deci;
	int i = 0;
	char hex [MAX];

	printf ("Enter the decimal value:");
	scanf ("%d", &deci);
	printf ("Verifying using %%x: %x\n\n",deci);
	while (deci){
		if ((hex [i] = (deci % 16)) >= 10)
			hex [i] = hex [i] - 10 + 'A';
		else
			hex [i] += '0';

		deci /= 16;
		i++;
	}
	hex [i] = '\0';

	reverse (hex);

	printf ("By Programmed, Hexadecimal: ");
	for (i = 0; i < strlen (hex); i++)
		printf ("%c", hex [i]);
	
	putchar ('\n');
	putchar ('\n');
}

void reverse (char hex[]){
	int i, j;
	char c;
	for (i = 0, j = strlen(hex) -1; i < j; i++, j--)
		c = hex [i], hex [i] = hex [j], hex [j] = c;
}	
