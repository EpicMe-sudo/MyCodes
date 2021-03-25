#Makefile

CC = /usr/bin/gcc
RM = /bin/rm

CFLAGS = -g -Wall -std=c99

SOURCES = Sbox.c FandG.c KeySchedule.c seed.c
HEADERS = Sbox.h FandG.h KeySchedule.c seed.h

all : test/test_exe

.PHONY: clean test

test:
	./test/test_exe

clean :
	$(RM) -rf *.o test/test_exe