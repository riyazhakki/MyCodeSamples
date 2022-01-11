/* ex28_vt510.h: 
			Fine grained terminal control
	The following macros are directly dervied from the programmers' reference manual of the vt510 terminalsl   */

# include <stdio.h>
# include <stdlib.h>
# include "ex28_vt510.h"

int main () {
	clear_screen ( );
	set_cursor ( 4, 10 );
	printf ( "AT 4, 10" );
	set_cursor ( 10, 20 );
	set_bold ( );
	printf ( "Bold Characters " );
	set_cursor ( 14, 1 );
	set_double_tops ( );
	printf ( "Uttara Academy" );
	set_cursor ( 15, 1 );
	set_double_bottoms ( );
	printf ( "Uttara Academy" );
	set_cursor ( 23, 1 );
}
	
