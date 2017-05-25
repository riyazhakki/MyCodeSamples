/* Recognise arrow keys and editing keys.
Modify the program to handle additional special keys. */

# define NOT_YET_SET	1000
# define UP_ARROW		1001
# define DN_ARROW		1002
# define LT_ARROW		1003
# define RT_ARROW		1004
# define EXIT_PROGRAM	'Q'
# define ESC			 27

int get_char ( );
void raw ( );
void canonical ( );


