CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

TARGET = todo

$(TARGET): main.o todo.o utils.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o todo.o utils.o

main.o: main.c todo.h
	$(CC) $(CFLAGS) -c main.c

todo.o: todo.c todo.h
	$(CC) $(CFLAGS) -c todo.c

utils.o: utils.c todo.h
	$(CC) $(CFLAGS) -c utils.c

.PHONY: clean
clean:
	rm -rf *.o $(TARGET)
