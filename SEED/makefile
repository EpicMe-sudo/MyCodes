#Makefile

CC = /usr/bin/gcc
RM = /bin/rm

CFLAGS = -g -Wall -std=c99
NISTFLAGS  = -Wno-unused-result -O3 -fomit-frame-pointer -march=native -std=c99 

SOURCES = Sbox.c FandG.c KeySchedule.c seed.c
HEADERS = Sbox.h FandG.h KeySchedule.c seed.h

mSOURCES = fips202.c rng.o Sbox.c FandG.c KeySchedule.c MaskingFunction.c MaskedSbox.c MaskedFandG.c MaskedSeed.c
mHEADERS = fips202.h rng.h Sbox.h FandG.h KeySchedule.c MaskingFunction.h MaskedSbox.h MaskedFandG.h MaskedSeed.h
all : test/SEED_EXE \
	  test/MASKEDSEED_EXE

test/SEED_EXE : $(SOURCES) $(HEADERS) test/test_seed.c
	$(CC) $(CFLAGS) -o $@ $(SOURCES) test/test_seed.c -lm

test/MASKEDSEED_EXE : $(mSOURCES) $(mHEADERS) test/test_maskedseed.c
	$(CC) $(CFLAGS) -o $@ $(mSOURCES) test/test_maskedseed.c -lcrypto

rng.o : rng.c
	$(CC) $(NISTFLAGS) -c rng.c -lssl -lcrypto -ldl -lpthread -o $@ 

.PHONY: clean test

test:
	./test/SEED_EXE
	./test/MASKEDSEED_EXE

clean :
	$(RM) -rf *.o test/SEED_EXE