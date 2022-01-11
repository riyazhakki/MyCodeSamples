/* variable arguments using standard macros defined in stdarg.h */

# include <stdio.h>
# include <stdarg.h>

void myprintf (char *,...);

main () {
	myprintf ("%d%f%s",10, 23.4,"Hello");
}

void myprintf (char *args,...){
	va_list va;
	int d;
	double f;
	char *s;

	va_start ( va, args );

	while ( *args ) {

		switch ( *args++ ) {
			case 'd' : 	
						d = va_arg( va, int );
						printf ("%d\n", d );
						break;
			case 'f' : 	
						f = va_arg( va, double );
						printf ("%f\n", f );
						break;
			case 's' : 	
						s = va_arg( va, char *);
						printf ("%s\n", s );
						break;
		}
	}
	va_end ( va );
}
