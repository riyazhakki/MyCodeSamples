/**********************************************************************
minils.c: Teat the command line arguments as directory names and display
	their contents.
	Use opendir (3) to open a directory file.
	Use readdir (3) to read successive entries.
	Use stat (2) to find details about each entry.
	ls -Rila
*************************************************************************/

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <pwd.h>
# include <time.h>

void my_ls ( char * );
void display ( char * , struct stat *);
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
				for ( j = 1; argv[i][j] != '\0'; j++) {
					switch ( argv [i][j] ) {
						case 'a' : hidden_flag = 1;
									break;
						case 'i' : inode_flag = 1;
									break;
						case 'l' : list_flag = 1;
									break;
						case 'R' : recursive_flag = 1;
									break;
						default	 : 
printf ("%c is invalid option, use - <a/i/R/l> option(s) only:)\n", argv[i][j]);
									exit (1);	
					}
				}
			}
			else {
				fprintf ( stderr, "mini_ls:Usage: -<a/i/l/R>\n");
				exit (1);
			}
		}
	}
	if ( argc == 2 && argv[1][0] == '-' && argv[2] == NULL )
		my_ls (".");


	for ( i = 1; i < argc; i++) {	// skip a.out
		if (argv[i][0] != '-') {
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
		if ( !hidden_flag && dp->d_name [0] == '.') 
				continue; 

		sprintf (fpath, "%s/%s", path, dp->d_name );
		if ( stat ( fpath, &stbuf ) == -1 ) {
			fprintf (stderr, "stat: can't access %s\n", fpath);
			return;
		}
		if ( ( stbuf.st_mode & S_IFMT ) == S_IFDIR ) {

			sprintf (dname, "%s/", dp->d_name );  // append '/' to dirfile

			if ( list_flag )
				display_list ( dname , &stbuf);
			else
				display ( dname , &stbuf);

			if ( strcmp ( dp->d_name, "." ) == 0 ||
				 strcmp ( dp->d_name, ".." ) == 0 )
					continue;	// goes to next directory entry

			sprintf ( dpath, "%s/%s", path, dp->d_name ); 
			dirs = realloc ( dirs, ++ndirs * sizeof (char * ) );
			* ( dirs + ( ndirs -1 ) ) = malloc ( strlen ( dpath ) + 1 );
			strcpy ( dirs [ ndirs - 1 ], dpath );

		}
		else {
			if ( list_flag )
				display_list ( dp->d_name , &stbuf);
			else
				display ( dp->d_name , &stbuf);
		}
	}
	closedir ( dfd );
	
	if ( recursive_flag ) {
		if ( ndirs ) {
			for ( i = 0; i < ndirs; i++ ) {
				printf ("\n\n%s:\n", dirs[i] );
				my_ls ( dirs [i] );
			}
		}
	}
}

void display ( char * name, struct stat *stbuf) {
static int i = 0;

if ( (stbuf->st_mode & S_IFMT) != S_IFDIR && 
	(stbuf->st_mode & 00007) == 00005)
		strcat (name, "*");

	if ( inode_flag ) {
		printf ( "%d %-22s", stbuf->st_ino, name );
		if ( ++i % 2 == 0 )
			putchar ('\n');
	}
	else{
		if ( ++i % 4 == 0 )
			putchar ('\n');
		printf ( "%-22s", name );
	}

}

void display_list ( char * name, struct stat *stbuf ) {
	struct tm *t_stamp;
	struct passwd *usr_info, *grp_info;
	time_t *atime;
	char perm [] =  "----------";
	
	usr_info = getpwuid ( stbuf->st_uid );
	grp_info = getpwuid ( stbuf->st_uid );
	
	*atime = stbuf->st_atime;
	t_stamp = localtime ( atime );	

	if ( (stbuf->st_mode & S_IFMT ) == S_IFDIR ) 
		perm[0] = 'd';

	switch ( (stbuf->st_mode & 00700) ) {		
		case 00700: perm [1] = 'r';
					perm [2] = 'w';
					perm [3] = 'x';
					break;
		case 00600: perm [1] = 'r';
					perm [2] = 'w';
					break;
		case 00400: perm[1] = 'r';
					break;
		case 00200: perm[2] = 'w';
					break;
		case 00100: perm[3] = 'x';
					break;
	}

	switch ( (stbuf->st_mode & 00070) ) {		
		case 00070: perm [4] = 'r';
					perm [5] = 'w';
					perm [6] = 'x';
					break;
		case 00060: perm [4] = 'r';
					perm [5] = 'w';
					break;
		case 00040: perm[4] = 'r';
					break;
		case 00020: perm[5] = 'w';
					break;
		case 00010: perm[6] = 'x';
						break;
	}
	
	switch ( (stbuf->st_mode & 00007) ) {		
		case 00007: perm [7] = 'r';
					perm [8] = 'w';
					perm [9] = 'x';
					break;
		case 00006: perm [7] = 'r';
					perm [8] = 'w';
					break;
		case 00004: perm[7] = 'r';
					break;
		case 00002: perm[8] = 'w';
					break;
		case 00005: perm[9] = 'x';
					break;
	}
	if ( inode_flag )
		printf ( "%-9d", stbuf->st_ino );
	printf ("%-10s", perm);
	printf ("%2d", stbuf->st_nlink);
	printf ("%6s", usr_info->pw_name);
	printf ("%6s", grp_info->pw_name);
	printf ("%9d", stbuf->st_size);
	printf (" %3s", get_mon_name (t_stamp->tm_mon));
	printf (" %02d", t_stamp->tm_mday );
	printf (" %02d", t_stamp->tm_hour);
	printf (":%02d", t_stamp->tm_min);
	if ( (stbuf->st_mode & S_IFMT) != S_IFDIR && 
		(stbuf->st_mode & 00007) == 00005)
			strcat (name, "*");
	printf (" %-20s", name );
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
