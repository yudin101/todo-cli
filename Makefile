CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

TARGET = todo
TEST_RUNNER = test

PREFIX = $(HOME)/.local
BIN = $(PREFIX)/bin
DATA_DIR = $(PREFIX)/share/todo
TEMP_DIR = /tmp/todo

all: $(TARGET)

main.o: main.c todo.h
	$(CC) $(CFLAGS) -c main.c

todo.o: todo.c todo.h
	$(CC) $(CFLAGS) -c todo.c

utils.o: utils.c todo.h
	$(CC) $(CFLAGS) -c utils.c

test.o: test.c todo.h
	$(CC) $(CFLAGS) -c test.c

$(TARGET): main.o todo.o utils.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o todo.o utils.o

test_runner: todo.o utils.o test.o
	$(CC) $(CFLAGS) -o $(TEST_RUNNER) todo.o utils.o test.o

.PHONY: clean install uninstall purge test

test: test_runner
	@mkdir -p $(TEMP_DIR)
	@bash -c 'trap "rm -rf $(TEMP_DIR)" EXIT; \
	./$(TEST_RUNNER) > /dev/null 2>&1 || (./$(TEST_RUNNER) && exit 1)'
	@echo "All Tests Passed!"

clean:
	rm -f *.o $(TARGET) $(TEST_RUNNER)
	rm -rf $(TEMP_DIR)

install:
	mkdir -p $(BIN)
	mkdir -p $(DATA_DIR)
	cp $(TARGET) $(BIN)

uninstall:
	rm -f $(BIN)/$(TARGET)

purge: clean uninstall
	rm -rf $(DATA_DIR)

