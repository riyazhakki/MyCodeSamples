// 	convert /*....   */ style comments //	to   // ..	style 
# include <stdio.h>

enum states { NORMAL, SLASH, STAR, END_STAR, STRING, NEWLINE };

main (){
	int c;
	int state = NORMAL;
	int pstate = NORMAL; 

	while ((c = getchar()) != EOF){
	
		switch (state){
			case NORMAL	:	if (c == '/'){
								putchar (c);
								state = SLASH;
							}else if (c == '"'){
								putchar (c);
								pstate = NORMAL;
								state = STRING;
							}
							else 
								putchar (c);
							break;
			case STRING	:	if (c == '"'){
								putchar (c);
								state = pstate;
								}
							else
								putchar (c);
							break;
			case SLASH	:	if (c == '*'){
								putchar ('/');
								state = STAR;
							}else if (c == '"'){
								putchar (c);
								pstate = SLASH;
								state = STRING;
							}
							else{
								putchar (c);
								state = NORMAL;
							}
							break;
			case STAR	:	if (c == '*'){
								state = END_STAR;
							}else if (c == '"'){
								putchar (c);
								pstate = STAR;
								state = STRING;
							}
							else if (c == '\n'){
								putchar (c);
								state = NEWLINE;
							}
							else
								putchar (c);
						break;
			case NEWLINE	:	if (c == '*'){
									state = END_STAR;
								}else if (c == '"'){
									putchar (c);
									pstate = STAR;
									state = STRING;
								}
								else
									printf ("//");
									putchar (c);
						break;

			case END_STAR	:	if (c == '/'){
									putchar ('\n');
									state = NORMAL;
								}else if (c == '"'){
									putchar (c);
									pstate = END_STAR;
									state = STRING;
								}
								else{
									putchar ('*');
									putchar (c);
									state = STAR;
								}
								break;
		}	//end of switch
		if (c == EOF){
			if (state != NORMAL){
				printf ("Invalid comment.....!\n");
				state = NORMAL;
			}
		}
	}	//end of while
}	//end of main
