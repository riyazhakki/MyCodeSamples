# include <stdio.h>
# include <ncurses.h>

main () {
	
	initscr();
	start_color();
	init_pair (1, COLOR_RED, COLOR_BLACK );
	attron (COLOR_PAIR (1));

	if ( has_colors() == TRUE )
		printf ("colors supported...\n");
	printw ("Hellow world...!\n");

	refresh();
	endwin();
}
