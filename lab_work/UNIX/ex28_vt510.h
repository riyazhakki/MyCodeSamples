/* ex28_vt510.h: 
			Fine grained terminal control
	The following macros are directly dervied from the programmers' reference manual of the vt510 terminalsl   */

	# define set_cursor(row, col)  printf ("\033[%d;%dH",row,col)
	# define clear_screen() 		printf ("\033[2J")
	# define set_bold()				printf ("\033[1m")
	# define set_normal()			printf ("\033[0m")
	# define set_double_tops()		printf ("\033#3" )
	# define set_double_bottoms()	printf ("\033#4" )
	# define set_single()			printf ("\033#6" )


