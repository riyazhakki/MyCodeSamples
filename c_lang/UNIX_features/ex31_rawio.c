/* Recognise arrow keys and editing keys.
Modify the program to handle additional special keys. 

Do raw I/O from keyboard and return ArrowKey strokes as suitable integer values
to be used by the application   */

# include <termios.h>
# include <fcntl.h>
# include "ex31_rawio.h"

int get_char ( ) {
	char c, buf;
	int nread;

	while ( read ( 0, &c, 1 ) != 1 ) ;
	if ( c == ESC ) {
		nread = read ( 0, &buf, 1 );
		if ( nread == 0 || nread == -1 ) return c;
		if ( buf == '[' ) {
			nread = read ( 0, &buf, 1 );
			if ( nread == 0 || nread == -1 )
				return NOT_YET_SET;
			switch ( buf ) {
				case 'A' : return UP_ARROW;
				case 'B' : return DN_ARROW;
				case 'C' : return RT_ARROW;
				case 'D' : return LT_ARROW;
			}
		}
		return NOT_YET_SET;
	}
	return c;
}
static struct termios save;

void raw ( ) {
	struct termios get; 
	int val;

	val = fcntl ( 0, F_GETFL, 0 );
	val |= ( O_NONBLOCK | O_ASYNC );
	fcntl ( 0, F_SETFL, val );
	tcgetattr ( 0, &get );
	save = get;
	get.c_lflag &= ~(ICANON | ECHO | ECHOE );
	get.c_oflag &= ~OPOST;
	get.c_cc[VMIN] = 1;
	get.c_cc[VTIME] = 2;
	tcsetattr ( 0, TCSANOW, &get );
}

void canonical ( ) {
	tcsetattr ( 0, TCSANOW, &save );
}

