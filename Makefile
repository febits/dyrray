CC=gcc
CFLAGS=-Wall -Wextra -pedantic -O3 -g
CINCLUDE=-I./include/
CFLAGS+=$(CINCLUDE)

BUILD_DIR=build

BENCH_SRC=$(wildcard benchmark/*.c)
BENCH_BIN=$(patsubst %.c, $(BUILD_DIR)/%, $(BENCH_SRC))

SRC=$(wildcard src/*.c)
BIN=$(BUILD_DIR)/dyrray-test

.PHONY: default clean always bench
default: always $(BIN) $(BENCH_BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/%: %.c
	$(CC) $(CFLAGS) src/dyrray.c $< -o $(BUILD_DIR)/$(notdir $@)

bench:
	-./build/bench

always:
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
