/* 06. Read a string more than 25 char's.  If it contains a specific substring
	(say, unix), print it; else discard it.  */

# include <stdio.h>
# define MAX 26

int getline (char *, int);
int strindex (char *, char *);

main (){
	char line [MAX];
	char pattern [MAX];
	int i = 0;
	
	printf ("Enter the pattern:");
	scanf ("%s", pattern);
	getchar(); 					//bypass \n	
	printf ("Enter the string:");
	while (getline(line, MAX) > 0){ 
		if (strindex (line, pattern) >= 0 ){
			printf ("%s", pattern);
		}
	}
	return 0;
}

int getline (char str[], int lim){
	int c, i = 0;

	while ( --lim > 0 && ((c = getchar()) != EOF) && (c != '\n'))
		str [i++] = c;
	if (c == '\n')
		str [i++] = c;
	str[i] = '\0';
	return i;
}

int strindex (char s[], char p[]){
	int i, j, k;
	for (i = 0; s[i] != '\0'; i++){
		for (j = i, k = 0; p[k] != '\0' && s[j] == p[k]; j++, k++)
			;	
		if (k > 0 && p[k] == '\0')
		return i;
	}
	return -1;
}

