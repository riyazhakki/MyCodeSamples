/* myprintf.c:
	prototype : myprntf (const char *, ... )
	Conversions to be handled: %% %d %nd %s
	Use macros from header firle to pick up arguments
	Use printf to do actual conversions  */

# include <stdio.h>

# define va_next(type) val = (type *) param; param += sizeof (type);

void myprintf (char *, ... );

main ( ) {
	myprintf ("%s%d%%%10f", "Riyaz", 100, 20.3);
}

void myprintf (char *line, ... ) {

	char * p, *param;
	int n = 0;
	int ival;
	void *val;

	p = line;

	param = (char *) (&line +1) ;

	while (*p) {
		switch (*p) {

			case '%' :if ( *(p+1) == '%' ) { putchar ('%'); p++; } break;
			
			case '0' : case '1' : case '2' : case '3' : case '4' : 
			case '5' : case '6' : case '7' : case '8' : case '9' : 
						n = atoi(p); 
						while (n--) putchar (' ');
						break;

			case 'd' : 	
						va_next(int); 					
						printf ("%d", * (int *)val);
						break;

			case 'f' : 	
						va_next(double); 					
						printf ("%f", *(double *)val);
						break;

			case 's' :  
						printf ("%s", *(char **)param );	
						param += sizeof (char *);
						break;
		}
		p++;
	}
	putchar ('\n');
}

