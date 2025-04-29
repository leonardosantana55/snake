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
OBJS=snake.c enteties.c utils.c events.c render.c
LINKER_FLAGS=-lSDL2 -lSDL2_image -Wall -lSDL2_ttf
LIBRARY_PATHS =-LC:\Users\XQ6460\Downloads\c\mingw64\x86_64-w64-mingw32\lib
OBJ_NAME=prog

all:$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -g -o $(OBJ_NAME) $(LIBRARY_PATHS) $(LINKER_FLAGS)
clean:
	rm -f $(OBJS)


## statically compile SDL2
## Link for stackoverflow answer: https://stackoverflow.com/questions/17620884/static-linking-of-sdl2-libraries

## Compiler and flags
##CXX = g++
##LINKER_FLAGS= -static
##LINKER_FLAGS += `pkg-config --libs --static SDL2`
##LINKER_FLAGS += `pkg-config --libs --static SDL2_ttf`
##LINKER_FLAGS += `pkg-config --libs --static SDL2_Image`
##LINKER_FLAGS += `pkg-config --libs --static SDL2_Mixer`
##LINKER_FLAGS += -lbrotlicommon -lsharpyuv
##CXXFLAGS = -lmingw32 -lws2_32 -lSDL2main -lSDL2 -lSDL2_Image -lSDL2_TTF -lSDL2_Mixer
##
##TARGET = <my_program>.exe
##
##SRC = <my_program>.cpp
##
##$(TARGET): $(SRC)
##    $(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS) $(LINKER_FLAGS)
