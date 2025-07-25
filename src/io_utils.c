#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/io_utils.h"
#include "../include/int_group.h"

input_data *get_input_data(int argc, char *argv[]) {
    input_data *input_data = malloc(sizeof(input_data));
    if (!input_data) {
        printf("Erro: alocacao de memoria (input_data)\n");
        exit(EXIT_FAILURE);
    }
    input_data->thread_quantity = atoi(argv[1]);

    if (input_data->thread_quantity != 2 &&
        input_data->thread_quantity != 4 &&
        input_data->thread_quantity != 8) {
        printf("Capacidade de threads incorreta!\n");
        exit(EXIT_FAILURE);
    }

    int files_count = 0;
    input_data->file_names = malloc(sizeof(char *) * (argc - 4));
    if (!input_data->file_names) {
        printf("Erro: alocacao de memoria (input_data->file_names)\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 2; i < argc - 2; i++) {
        input_data->file_names[files_count] = malloc(sizeof(char) * FILE_NAME_LENGTH);
        if (!input_data->file_names[files_count]) {
            printf("Erro: alocacao de memoria (input_data->file_names[%d])\n", files_count);
            exit(EXIT_FAILURE);
        }
        strcpy(input_data->file_names[files_count++], argv[i]);
    }

    input_data->files_quantity = files_count;
    input_data->output_file = argv[argc - 1];

    return input_data;
}

void read_numbers_from_file(char *file_name, int_group *group) {
    FILE *file = fopen(file_name, "r");

    if (!file) {
        printf("Erro: abertura de arquivo de numeros inteiros para leitura\n");
        exit(EXIT_FAILURE);
    }

    char file_line[MAX_FILE_LINE_LENGTH];
    
    while (fgets(file_line, MAX_FILE_LINE_LENGTH, file)) {
        int number = atoi(file_line);

        if (sizeof(group->numbers) < sizeof(int) * (group->length + 1)) {
            group->numbers = realloc(group->numbers, sizeof(int) * group->length * RESIZE_THRESHOLD);
            if (!group->numbers) {
                printf("Erro: alocacao de memoria (group->numbers)\n");
                exit(EXIT_FAILURE);
            }
        }

        group->numbers[group->length] = number;
        group->length++;
    }

    fclose(file);
}

void write_output_data(int_group *group, char *output_file) {
    FILE *file = fopen(output_file, "w+");

    if (!file) {
        printf("Erro: escrita de numeros inteiros em arquivo de saida\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < group->length; i++)
        if (i != group->length - 1)
            fprintf(file, "%d\n", group->numbers[i]);
        else
            fprintf(file, "%d", group->numbers[i]);

    fclose(file);
}
