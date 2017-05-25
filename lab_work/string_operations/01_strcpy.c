/*****************************************************************************
01_strcpy.c: 
Note: Boundary condition handling is to be done carefully. Memory availability
	for output also has to be carefully thoughtout. Don't forget the '\0' at 
	the end of each string (input or output).
*****************************************************************************/

# include <stdio.h>
# include <stdlib.h>

char * strcpy ( char *, char * );
int strlen ( char * );

main ( ) {
	char *src = "Hello World";
	char *dst;

	dst =  malloc ( strlen (src) + 1 );
	strcpy (src, dst);
	printf ("%s", dst);
}

int strlen ( char *str ) {
	int l;
	while ( *++str )
		l++;
	return l;
}

char * strcpy ( char * src, char *dst ) {
	char *temp = dst;

	while ( *dst++ = *src++ );
	return temp;
}

char * strcpy_a ( char * src, char *dst ) {
	char *temp = dst;

	while (*src)
		*dst++ = *src++;
	*dst = '\0';
	return temp;
}

char * strcpy_c ( char * src, char *dst ) {
	char *temp = dst;

	do 
		*dst++ = *src ;
	while (*src++);
	return temp;
}
