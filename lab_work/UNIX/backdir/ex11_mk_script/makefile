app		:	app.o stack.o
			@echo linking
			cc -o app app.o stack.o

app.o	:	app.c stack.h
			cc -c app.c

stack.o:	stack.c stack.h 
			cc -c stack.c
