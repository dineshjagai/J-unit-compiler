all : jc

stack.o : stack.c stack.h  
	clang -c -g -Wall stack.c

token.o : token.c token.h
	clang -c -g -Wall token.c

compiler.o : compiler.c compiler.h
	clang -c -g  -Wall compiler.c

jc.o : jc.c token.h compiler.h
	clang -c -g  -Wall jc.c

jc : token.o compiler.o jc.o stack.o 
	clang -o  jc token.o compiler.o jc.o stack.o

clean : 
	rm trace*.o
	
