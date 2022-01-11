# include <stdio.h>
# include <fcntl.h>

void lock_field ( int fd, int ptr,  int size ){ 

	if ( lseek ( fd, ptr, SEEK_SET ) < 0 ){
		fprintf ( stderr, "Error in seeking file...!\n" );
		return;
	}
	
	while ( lockf ( fd, F_TLOCK, size ) == -1 ){
		sleep (2);
	}
}

void unlock_field ( int fd, int ptr, int size ) {
	lseek ( fd, ptr, SEEK_SET );
	lockf ( fd, F_ULOCK, size );
}
	
