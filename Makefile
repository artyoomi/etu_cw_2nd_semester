PROJ_NAME = cw
CC = gcc
FLAGS =-g -c

OBJ = main.o \
	  bmp.o \
	  print_funcs.o \
	  rgbfilter.o \
	  parse_funcs.o \
	  draw.o \
	  exchange.o \
	  freq_color.o \
	  etc.o \
	  image.o

main: $(OBJ)
	$(CC) -g -Wall -Werror  -o $(PROJ_NAME) $(OBJ) -lm
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

draw.o: lib/draw.c include/draw.h
	$(CC) $(FLAGS) lib/draw.c

exchange.o: lib/exchange.c include/exchange.h
	$(CC) $(FLAGS) lib/exchange.c

freq_color.o: lib/freq_color.c include/freq_color.h
	$(CC) $(FLAGS) lib/freq_color.c

etc.o: lib/etc.c include/etc.h
	$(CC) $(FLAGS) lib/etc.c

image.o: lib/image.c include/image.h
	$(CC) $(FLAGS) lib/image.c
