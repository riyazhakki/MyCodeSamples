all : create deposit withdraw balance change clean

deposit : deposit.c sb.h
			cc -o deposit deposit.c 

withdraw : withdraw.c sb.h
			cc -o withdraw withdraw.c 

balance : balance.o display.o
			cc -o balance balance.o display.o

balance.o : balance.c sb.h
			cc -c balance.c  
			
change 	: change.c sb.h
			cc -o change change.c 

create	:  create.c sb.h
			cc -o create create.c 

display.o : display.c
			cc -c display.c

clean	:
		@-unlink display.o
		@-unlink balance.o
