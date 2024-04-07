CC = g++
FLAGS =-g -c

main: main.o bmp.o print_funcs.o exception.o
	$(CC) -g -o main main.o bmp.o print_funcs.o exception.o
	rm *.o

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

bmp.o: bmp.cpp bmp.h
	$(CC) $(FLAGS) bmp.cpp

print_funcs.o: print_funcs.cpp print_funcs.h
	$(CC) $(FLAGS) print_funcs.cpp

exception.o: exception.cpp exception.h
	$(CC) $(FLAGS) exception.cpp
