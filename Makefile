##-----------------------------------------------#
## Makefile for UNIX systems #
## using a GNU C compiler #
##-----------------------------------------------#
##
## Compiler flags:
## -g -- Enable debugging
## -Wall -- Turn on all warnings (not used since it gives away
## the bug in this program)
## -D__USE_FIXED_PROTOTYPES__
## -- Force the compiler to use the correct headers
## -ansi -- Don't use GNU extensions. Stick to ANSI C.

CC=gcc
#CFLAGS=-g -D__USE_FIXED_PROTOTYPES__ -ansi
# OBJS: All the files to be compiled:
OBJS=snake.c enteties.c utils.c
LINKER_FLAGS=-lSDL2 -lSDL2_image -Wall
LIBRARY_PATHS =-LC:\Users\XQ6460\Downloads\c\mingw64\x86_64-w64-mingw32\lib
OBJ_NAME=prog

all:$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(OBJ_NAME) $(LIBRARY_PATHS) $(LINKER_FLAGS)
clean:
	rm -f $(OBJS)
