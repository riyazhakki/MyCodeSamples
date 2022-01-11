/* 11. Sort input for integers, doubles & strings and print using %d
	%f and %s formats (Ex: xyz123 is invalid)	*/

# include <stdio.h>
# include <ctype.h>
# include <string.h>
# include <stdlib.h>

# define MAX 300

main(){

	int *ints;
	ints = NULL;
	int nints = 0;
	int i = 0;
	int c;

	double *doubles ;
	doubles = NULL; 
	int ndoubles = 0;

	char line [MAX];
	char **strings;
	strings = NULL; 
	char nstrings = 0;
	char *p = NULL;
	char save;
	char *item = NULL;

	char **invalids = NULL;
	int ninvalids = 0;
	int	count = 0;

	enum Type { Int, Double, String, FloatString, Invalid };
	enum Type flag;

	while ((fgets(line, MAX, stdin)) ){
		p = line;

	while (1){
			// skip white spaces
			count = 0;
			while (*p == ' ' || *p == '\t' || *p == '\n'){
				p++;
			}
			item = p;
			if(!*p)
				break;
			flag = Int;

			while ( *p != ' ' && *p != '\t' && *p != '\n'){

				if (*p == '.' && flag != Double && flag != FloatString && flag != Invalid)
					flag = Double;
				else if (flag == Double && *p == '.' )
					flag = FloatString;
				else if (!isdigit (*p) && flag == Int && count == 0)
					flag = String;
				else if (flag == String && isdigit (*p)&& *p != '.' )
					flag = Invalid;
				else if (!isdigit(*p) && (flag == Int || 
							flag == Double || flag == FloatString) && count){
					if ( flag == FloatString && !isdigit(*p) )
						;
					else
					flag = Invalid;
				}
				count++;
				p++;
			} //EOWhile	

			save = *p;
			*p = '\0';

			if (flag == Int){
				ints = realloc (ints, ++nints * sizeof(int));
				ints [nints -1] = atoi (item);		
			}
			if (flag == Double){
				doubles = realloc (doubles, ++ndoubles * sizeof (double));
				doubles [ndoubles - 1] = atof (item);		
			}
			if (flag == String || flag == FloatString){
				strings = realloc (strings, ++nstrings * sizeof (char *));
				*(strings + (nstrings - 1)) = malloc ( strlen (item) + 1);
			//	strings  [nstrings - 1] = malloc ( strlen (item) + 1);
				strcpy (strings [nstrings - 1], item);
			//	strings [nstrings - 1] = strdup (item);
			}
			if ( flag == Invalid){
				invalids = realloc (invalids, ++ninvalids * sizeof (char *));
				invalids [ninvalids - 1] = strdup (item);
			}
			*p = save;
		}
	} // EOWhile

//===========Seggragation=========

	if (nints){
		printf ("*********INTEGERS**********\n");
		for (i = 0; i < nints; i++){
			printf("%d\n", ints[i]);
		}
	}
	if (ndoubles){
		printf ("*********FLOATS**********\n");
		for (i = 0; i < ndoubles;  i++){
			printf("%f\n", doubles[i]);
		}
	}
	if (nstrings){
		printf ("************STRINGS***********\n");
		for (i = 0; i < nstrings; i++){
			printf ("%s\n", strings[i]);
		}
	}
	if (ninvalids){
		printf ("*********INVALIDS**********\n");
		for (i = 0; i < ninvalids; i++){
			printf("%s\n", invalids[i]);
		}
	}

//*****FREE MEMORY*********

	free (ints);
	free (doubles);
	for (i =0; i<nstrings; i++)
		free (strings [i]);

	free (strings);

}//EOmain()
