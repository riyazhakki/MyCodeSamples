/* a simple varargs procedure assmes CISC CPU (params always on stack)
	may not work for a RISC CPU architectre */

# include <stdio.h>

	int vadd ( int nint, ... );

	main ( ) {
		printf ("%d\n", vadd (4, 10, 20, 30, 40, 50 ));
	}

	int vadd ( int nint, ... ) {
		char * va_list;
		int total = 0;

		va_list = (char *) (& nint + 1);
		while ( nint-- > 0 ) {
			total += *(int *) va_list;
			va_list += sizeof (int);
		}
		return total;
	}
