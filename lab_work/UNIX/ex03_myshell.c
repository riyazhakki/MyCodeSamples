/* myshell.c : Read standard input lines 
				Seperate the line into words to form a sentance 
				Assume no special character processing  */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define MAX 40

main () {
	char line [MAX];
	char **word = NULL;
	char *p, *item, save;
	int nwords, i;

	printf ("My_Shell_R>");
	while ((fgets(line, MAX, stdin)) ){
		p = line;
		nwords = 0;
		while (1){

			while (*p == ' ' || *p == '\t' || *p == '\n')  p++;
												//Skip WSpaces

			item = p;
			if(!*p)  break;			// End of line

			while ( *p != ' ' && *p != '\t' && *p != '\n')  
				p++;  // Walk all chars till hit WSpace

			save = *p;  *p = '\0';

			word = realloc (word , ++nwords * sizeof (char *));
			word [nwords - 1] = strdup (item);

			*p = save;
		}
		word = realloc (word , ++nwords * sizeof (char *));
		word [nwords - 1] = NULL;

		switch ( fork () ) {
			case -1 : 	fprintf (stderr, "Can't forked...!\n");
						exit (1);

			case  0 :  	
					   	execvp ( *word, word );
				  	   	printf ("Invalid command....!\n");
						exit (0);
						break;
		}
		wait (NULL);
	printf ("My_Shell_R>");
	}
	exit (0);
}
	
