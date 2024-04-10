CC = gcc
FLAGS =-g -c

OBJ = main.o \
	  bmp.o \
	  print_funcs.o \
	  rgbfilter.o \
	  parse_funcs.o

main: $(OBJ)
	$(CC) -g -o main $(OBJ)
	rm *.o

main.o: main.c
	$(CC) $(FLAGS) main.c

bmp.o: lib/bmp.c include/bmp.h
	$(CC) $(FLAGS) lib/bmp.c

print_funcs.o: lib/print_funcs.c include/print_funcs.h
	$(CC) $(FLAGS) lib/print_funcs.c

rgbfilter.o: lib/rgbfilter.c include/rgbfilter.h
	$(CC) $(FLAGS) lib/rgbfilter.c

parse_funcs.o: lib/parse_funcs.c include/parse_funcs.h
	$(CC) $(FLAGS) lib/parse_funcs.c
