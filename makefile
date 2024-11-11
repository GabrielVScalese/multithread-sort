CC = gcc
C_FLAGS = -Wall -g
LD_FLAGS = -pthread
TARGET = mergesort
OBJS = main.o int_group.o io_utils.o thread_utils.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LD_FLAGS) -o $@ $(OBJS)

main.o: src/main.c ./include/int_group.h ./include/io_utils.h
	$(CC) $(C_FLAGS) -c src/main.c

int_group.o: src/int_group.c ./include/int_group.h
	$(CC) $(C_FLAGS) -c src/int_group.c

io_utils.o: src/io_utils.c ./include/io_utils.h
	$(CC) $(C_FLAGS) -c src/io_utils.c

thread_utils.o: src/thread_utils.c ./include/thread_utils.h
	$(CC) $(C_FLAGS) -c src/thread_utils.c

clean:
	rm -f $(TARGET) $(OBJS)
