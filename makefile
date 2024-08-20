CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -pthread
TARGET = program
OBJS = main.o int_group.o io_utils.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

main.o: src/main.c ./include/int_group.h ./include/io_utils.h
	$(CC) $(CFLAGS) -c src/main.c

int_group.o: src/int_group.c ./include/int_group.h
	$(CC) $(CFLAGS) -c src/int_group.c

io_utils.o: src/io_utils.c ./include/io_utils.h
	$(CC) $(CFLAGS) -c src/io_utils.c

clean:
	rm -f $(TARGET) $(OBJS)
