CC=gcc
CFLAGS=-Wall -Wextra -pedantic -O3 -g
CINCLUDE=-I./include/
CFLAGS+=$(CINCLUDE)
LDFLAGS=-lcmocka

BUILD_DIR=build

BENCH_SRC=$(wildcard benchmark/*.c)
BENCH_BIN=$(patsubst %.c, $(BUILD_DIR)/%, $(BENCH_SRC))

TEST_SRC=$(wildcard tests/*.c)
TEST_BIN=$(BUILD_DIR)/test-dyrray

SRC=$(wildcard src/*.c)
BIN=$(BUILD_DIR)/print-dyrray

.PHONY: default clean always bench tests
default: always $(BIN) $(BENCH_BIN) $(TEST_BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

$(TEST_BIN): $(TEST_SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) src/dyrray.c $^ -o $@

$(BUILD_DIR)/%: %.c
	$(CC) $(CFLAGS) src/dyrray.c $< -o $(BUILD_DIR)/$(notdir $@)

bench:
	-./build/bench

tests:
	-./build/test-dyrray

always:
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
