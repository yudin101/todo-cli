CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

TARGET = todo

PREFIX = $(HOME)/.local
BIN = $(PREFIX)/bin
DATA_DIR = $(PREFIX)/share/todo

all: $(TARGET)

main.o: main.c todo.h
	$(CC) $(CFLAGS) -c main.c

todo.o: todo.c todo.h
	$(CC) $(CFLAGS) -c todo.c

utils.o: utils.c todo.h
	$(CC) $(CFLAGS) -c utils.c

$(TARGET): main.o todo.o utils.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o todo.o utils.o

.PHONY: clean install uninstall purge

clean:
	-rm -r *.o $(TARGET)

install:
	mkdir -p $(BIN)
	mkdir -p $(DATA_DIR)
	cp $(TARGET) $(BIN)

uninstall:
	-rm -r $(BIN)/$(TARGET)

purge: clean uninstall
	rm -rf $(DATA_DIR)

