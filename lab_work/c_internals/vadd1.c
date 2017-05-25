/* a simple varargs procedure assmes CISC CPU (params always on stack)
	may not work for a RISC CPU architectre 
	vadd1.c : using macros va_start, va_next */

# include <stdio.h>
# include "varargs.h"

int vadd ( int nint, ... );


main ( ) {
	printf ("%d\n", vadd (4, 10, 20, 30, 40, 50 ));
}

int vadd ( int nint, ... ) {
	va_list va;
	int total = 0;
	
	va = va_start(nint);

	while ( nint-- > 0 ) {
		total += va_next(va,int); 
	}
	return total;
}
