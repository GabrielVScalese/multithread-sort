#ifndef IO_UTILS_H
#define IO_UTILS_H

#include "../include/int_group.h"
#define INITIAL_NUMBERS_LIST_LENGTH 10
#define MAX_FILE_LINE_LENGTH 100

typedef struct input_data {
    int thread_number;
    int *numbers;
    int numbers_quantity;
    char *output_file;
} input_data;

input_data *get_input_data(int argc, char *argv[]);

void write_output_data(int_group *group, char *output_file);

void print_numbers(int *numbers, int length);

void print_new_line();

#endif
