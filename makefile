#makefile for count.c in lab1
#adapted from lab0 makefile

CC=gcc
CGLAGS = -g -Wall

all: count

count: count.c
	$(CC) $(CFLAGS) -o count count.c

clean:
	rm count
