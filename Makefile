OBJS	= Shell.o StringVector.o
SOURCE	= Shell.c StringVector.c
HEADER	= Shell.h StringVector.h
OUT	= myshell
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

Shell.o: Shell.c
	$(CC) $(FLAGS) Shell.c 

StringVector.o: StringVector.c
	$(CC) $(FLAGS) StringVector.c 


clean:
	rm -f $(OBJS) $(OUT)