#Makefile

CC = /usr/bin/gcc
RM = /bin/rm

CFLAGS = -g -Wall -std=c99
TARGET = LEA_CPA

SOURCES = LEA128.c LEA_CPA.c
HEADERS = LEA128.h LEA_CPA.h

all : $(TARGET)

$(TARGET) : $(SOURCES) $(headers) main.c
	$(CC) $(CFLAGS) -o $@ $(SOURCES) main.c -lm

test:
	./LEA_CPA

clean :
	$(RM) -rf $(OBJS) $(TARGET)