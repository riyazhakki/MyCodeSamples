# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <curses.h>

int main ( void ) {

	int x, y;

	WINDOW * mainwin, *childwin;
	if ( (mainwin = initscr()) == NULL ){
		fprintf ( stderr, "Error initialising ncurses\n" );
		exit ( EXIT_FAILURE );
	}

	start_color ( );
	
	x = 10;
	y = 10;

	childwin = subwin (mainwin, 10, 10, y, x);
	box (childwin, 0, 0);

	mvaddstr ( 6, 32, " Hello world!" );
	
	if ( has_colors() && COLOR_PAIRS >= 13 ) {

		int n = 1;
		init_pair ( 1, COLOR_RED, COLOR_BLACK );
		init_pair ( 2, COLOR_GREEN, COLOR_BLACK );
		init_pair ( 3, COLOR_YELLOW, COLOR_GREEN );

		while ( n <= 3 ){

			color_set ( n, NULL );
			mvaddstr ( 6 + n, 32, " Hello World!" );
			n++;
		}
	}

	refresh ();
	sleep (3);

	delwin ( childwin );
	delwin ( mainwin );
	endwin ( );
	refresh ( );
	return EXIT_SUCCESS;
}
