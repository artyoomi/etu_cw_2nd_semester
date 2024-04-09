CC = gcc
FLAGS =-g -c

OBJ = main.o \
	  bmp.o \
	  print_funcs.o \
	  exception.o \
	  rgbfilter.o

main: $(OBJ)
	$(CC) -g -o main $(OBJ)
	rm *.o

main.o: main.c
	$(CC) $(FLAGS) main.c

bmp.o: bmp.c bmp.h
	$(CC) $(FLAGS) bmp.c

print_funcs.o: print_funcs.c print_funcs.h
	$(CC) $(FLAGS) print_funcs.c

exception.o: exception.c exception.h
	$(CC) $(FLAGS) exception.c

rgbfilter.o: rgbfilter.c rgbfilter.h
	$(CC) $(FLAGS) rgbfilter.c
