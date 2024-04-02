CC=gcc
CFLAGS=-Wall -Wextra -pedantic
CINCLUDE=-I./include/
CFLAGS+=$(CINCLUDE)

SRC=$(wildcard src/*.c)
BIN=dyrray

.PHONY: default
default: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm $(BIN)
