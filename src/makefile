CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -pthread
TARGET = program
OBJS = main.o int_group.o io_utils.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

main.o: main.c ../include/int_group.h ../include/io_utils.h
	$(CC) $(CFLAGS) -c main.c

int_group.o: int_group.c ../include/int_group.h
	$(CC) $(CFLAGS) -c int_group.c

io_utils.o: io_utils.c ../include/io_utils.h
	$(CC) $(CFLAGS) -c io_utils.c

clean:
	rm -f $(TARGET) $(OBJS)
