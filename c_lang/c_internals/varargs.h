
typedef char *va_list;

# define va_start(nint) (char *)(& nint + 1); 
# define va_next(va,int) *(int *) va; va += sizeof (int); 
