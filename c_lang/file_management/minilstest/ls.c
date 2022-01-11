# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <pwd.h>
# include <time.h>

void my_ls ( char * );
void display ( char * );
void display_list ( char *, struct stat *); 
char * get_mon_name ( int ); 

int hidden_flag, inode_flag, list_flag, recursive_flag;

main ( int argc , char * argv [] ) {
int i,j;

hidden_flag = inode_flag = list_flag = recursive_flag = 0;

if ( argc == 1 )
	my_ls (".");
else {
	for ( i = 0; i < argc; i++ ) {
		if ( argv [i][0] == '-' )
			if (argv [i][1] != '\0' ) {
				for ( j = 0; argv[i][j] != '\0'; j++) {
					switch ( argv [i][j] ) {
						case 'a' : hidden_flag = 1;
									break;
						case 'i' : inode_flag = 1;
									break;
						case 'l' : list_flag = 1;
									break;
						case 'R' : recursive_flag = 1;
									break;
		//				default	 : printf ("There is no such option\n");
					}
				}
			}
			else {
				fprintf ( stderr, "mini_ls:Usage: -<a/i/l/R>\n");
				exit (1);
			}
		}
	}

	printf ("a:%2d  i:%2d  l:%2d  R:%2d\n",
		hidden_flag, 
		inode_flag, 
		list_flag, 
		recursive_flag
	);

	for ( i = 1; i < argc; i++) {	// skip a.out
		if (argv[i][0] != '-') {
		printf ("my_ls ( %s )", argv[i] );
			my_ls ( argv[i] );
		}
	}
	putchar ('\n');
}

void my_ls (char *path ) {
	struct stat stbuf;
	struct dirent *dp; 			//directory pointer
	DIR *dfd;					// directory file descriptor
	char dname [ 50 ];
	char dpath [ 50 ];
	char fpath [ 50 ];
	char **dirs = NULL;
	int ndirs = 0;
	int i;

	if ( (dfd = opendir ( path ) ) == NULL ) {
		fprintf (stderr, "opendir: can't access %s\n", path);
		exit (0);
	}

	while ( ( dp = readdir ( dfd ) ) != NULL ) {
		if ( strcmp ( dp->d_name, "." ) == 0 ||
			 strcmp ( dp->d_name, ".." ) == 0 )
			 	continue;
		sprintf (fpath, "%s/%s", path, dp->d_name );
		if ( stat ( fpath, &stbuf ) == -1 ) {
			fprintf (stderr, "stat2: can't access %s\n", fpath);
			return;
		}
		if ( ( stbuf.st_mode & S_IFMT ) == S_IFDIR ) {

			sprintf ( dpath, "%s/%s", path, dp->d_name ); 

			dirs = realloc ( dirs, ++ndirs * sizeof (char * ) );
			* ( dirs + ( ndirs -1 ) ) = malloc ( strlen ( dpath ) + 1 );
			strcpy ( dirs [ ndirs - 1 ], dpath );

			sprintf (dname, "%s/", dp->d_name );
			//display ( dname );
			display_list ( dname , &stbuf);
		}
		else {
		//	display ( dp->d_name );
			display_list ( dp->d_name , &stbuf);
		}
	}

/*
	// Recursive call
	if ( ndirs ) {
		for ( i = 0; i < ndirs; i++ ) {
			printf ("\n\n%s:\n", dirs[i] );
			my_ls ( dirs [i] );
		}
	}
*/

}

void display ( char * name ) {
	printf ( "%-20s", name );
}

void display_list ( char * name, struct stat *stbuf ) {
	struct tm *t_stamp;
	struct passwd *usr_info, *grp_info;
	time_t *atime;
	char time_format [ 60 ];


	usr_info = getpwuid ( stbuf->st_uid );
	grp_info = getpwuid ( stbuf->st_uid );
	
	*atime = stbuf->st_atime;
	t_stamp = localtime ( atime );	


	sprintf ( time_format, "%3s %2d %02d",
				get_mon_name ( t_stamp->tm_mon ),
				t_stamp->tm_mday,
				t_stamp->tm_hour
//				t_stamp->tm_min
			);


/*	printf ( "%10d %6s %2d %6d %s %-20s\n", 
			stbuf->st_ino, 
			usr_info->pw_name,
			stbuf->st_nlink, 
			stbuf->st_size, 
			time_format,
			name  
		);
*/
	printf ("%8d", stbuf->st_ino);
	printf ("%2d", stbuf->st_nlink);
	printf ("%6s", usr_info->pw_name);
	printf ("%6s", grp_info->pw_name);
	printf ("%6d", stbuf->st_size);
	printf (" %3s", get_mon_name (t_stamp->tm_mon));
	printf (" %02d", t_stamp->tm_mday );
	printf (" %02d", t_stamp->tm_hour);
	printf (":%02d", t_stamp->tm_min);
	printf ("  %-20s", name );
	putchar ('\n');
}

char * get_mon_name ( int mon ) {
	switch ( mon ) {
		case 0 : return "Jan";    // no break needed
		case 1 : return "Feb";
		case 2 : return "Mar";
		case 3 : return "Apr";
		case 4 : return "May";
		case 5 : return "Jun";
		case 6 : return "Jul";
		case 7 : return "Agu";
		case 8 : return "Sep";
		case 9 : return "Oct";
		case 10 : return "Nov";
		case 11 : return "Dec";
	}
}
