/* myprintf.c:
	prototype : myprntf (const char *, ... )
	Conversions to be handled: %% %d %nd %s
	Use macros from header firle to pick up arguments
	Use printf to do actual conversions  */

# include <stdio.h>
# include <string.h>

//# define va_nexti(type) ival = *(type *) param; param += sizeof (type);

# define va_next(type) val = (type *) param; param += sizeof (type);

void myprintf (char *, ... );

main ( ) {
	myprintf ("%s","Hello");
	myprintf ("%d",10);
	myprintf ("%f",10.1);
	myprintf ("%d%5d",10,20);
	myprintf ("%%");
}



void myprintf (char *line, ... ) {
	char * p, *param;
	int n = 0;
	int ival;
	void *val;

	p = line;

	param = (char *) (&line +1) ;

	printf ("&line + 1 : %s \n", *(&line + 1) ); 
	printf ("param: %s \n", *param );	

	while (*++p) {
		switch (*p) {

			case '%' : if ( *(p+1) == '%' ) { putchar ('%'); p++; } break;

			case '1' :  n = 1 ; while (n--) putchar (' '); break;
			case '2' :  n = 2 ; while (n--) putchar (' '); break;
			case '3' :  n = 3 ; while (n--) putchar (' '); break;
			case '4' :  n = 4 ; while (n--) putchar (' '); break;
			case '5' :  n = 5 ; while (n--) putchar (' '); break;
			case '6' :  n = 6 ; while (n--) putchar (' '); break;
			case '7' :  n = 7 ; while (n--) putchar (' '); break;
			case '8' :  n = 8 ; while (n--) putchar (' '); break;
			case '9' :  n = 9 ; while (n--) putchar (' '); break;

			case 'd' : 	
						va_next(int); 					
						printf ("%d", * (int *)val);
						break;

			case 'f' : 	
						va_next(float); 					
						printf ("%f", *(float *)val);
						break;
			case 's' :  
						printf ("%s", *(&line + 1));
						break;

		}
	}
	putchar ('\n');
}

