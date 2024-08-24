#include <stdio.h>
#include <stdlib.h>
#include "../include/io_utils.h"
#include "../include/int_group.h"

input_data *get_input_data(int argc, char *argv[]) {
    input_data *input_data = malloc(sizeof(input_data));
    input_data->thread_number = atoi(argv[1]);

    int numbers_list_length = INITIAL_NUMBERS_LIST_LENGTH;
    int numbers_count = 0;
    input_data->numbers = malloc(sizeof(int) * numbers_list_length);

    for (int i = 2; i < argc - 2; i++) {
        FILE *file = fopen(argv[i], "r");
        char file_line[MAX_FILE_LINE_LENGTH];

        while (fgets(file_line, MAX_FILE_LINE_LENGTH, file)) {
            int number = atoi(file_line);

            if (numbers_count == numbers_list_length) {
                numbers_list_length *= RESIZE_THRESHOLD;
                input_data->numbers = realloc(input_data->numbers, sizeof(int) * numbers_list_length);
            }

            input_data->numbers[numbers_count++] = number;
        }

        fclose(file);
    }

    input_data->numbers_quantity = numbers_count;
    input_data->output_file = argv[argc - 1];

    return input_data;
}

void write_output_data(int_group *group, char *output_file) {
    FILE *file = fopen(output_file, "w");
    for (int i = 0; i < group->length; i++)
        if (i != group->length - 1)
            fprintf(file, "%d\n", group->numbers[i]);
        else
            fprintf(file, "%d", group->numbers[i]);

    fclose(file);
}

void print_new_line() {
    printf("\n");
}
