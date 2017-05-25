// 	convert /*....   */ style comments \
to   // ..	style 

# include <stdio.h>

enum states { NORMAL, SLASH, STAR, OLDSTYLE, NEWSTYLE, BACKSLASH, QUOTE};

main (){
	int c;
	int flag = 0;
	int state = NORMAL;
	int prev;

	while ((c = getchar()) != EOF){
	
		switch (state){
			case NORMAL	:	
				if (c == '/'){
					state = SLASH;
				}else if (c == '"'){
					putchar (c);
					state = QUOTE;
				}
				else 
					putchar (c);
			break;

			case QUOTE:
				if (c == '"'){
					putchar (c);
					state = NORMAL;
				}
				else
					putchar (c);
			break;

			case SLASH	:
				if (c == '*'){
					flag = 1;
					state = OLDSTYLE;
				}
				else if (c == '/'){
					flag = 1;
					state = NEWSTYLE;
				}
				else{
					putchar ('/');
					putchar (c);
					state = NORMAL;
				}
			break;

			case OLDSTYLE:
				if (c == '*'){
					state = STAR;
				}
				else if (c == '\n'){
					putchar (c);
					flag = 1;
				}
				else{
					if (flag){
						printf ("//");
						flag = 0;
					}
					putchar (c);
				}
			break;

			case STAR:
				if (c == '/'){
					putchar ('\n');
					state = NORMAL;
				}
				else if (c == '*')
					putchar (c);
				else{
					putchar (c);
					state = OLDSTYLE;
				}
			break;

			case NEWSTYLE:	
				if (c == '\\'){
					putchar (c);
					state = BACKSLASH;
				}
				else if (c == '\n'){
					putchar (c);
					state = NORMAL;
				}
				else{
					if(flag){
						printf("//");
						flag = 0;
					}
					putchar (c);
				}
			break;

			case BACKSLASH:
				putchar (c);
				state = NEWSTYLE;
			break;
		}		//end of switch
	}		//end of while
}		//end of main
