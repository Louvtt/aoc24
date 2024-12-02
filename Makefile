CC=gcc
CFLAGS=-O3 -g -ffast-math
DAYS=$(shell find . -name "day*" -type d)
DAYS_EXE=$(DAYS:./%=bin/%-exe)

.PHONY: all clean $(DAYS)

all: clean $(DAYS_EXE)

clean:
	rm -rf bin/*

day%.o: day%.c
	$(CC) $(CFLAGS) -c $< -o $@

bin/day%-exe: day%/main.c
	$(CC) $(CFLAGS) -DPART_ONE $< -o $@-p1
	$(CC) $(CFLAGS) -DPART_TWO $< -o $@-p2
