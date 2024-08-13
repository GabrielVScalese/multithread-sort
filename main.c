#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <getopt.h>

#define MAX_FILE_LINE_LENGTH 100
#define INITIAL_INPUT_NUMBERS_QUANTITY 10

// Tipos

typedef struct int_group
{
    int *numbers;
    int length;
} int_group;

typedef struct command_line_data
{
    int thread_number;
    int *numbers;
    int numbers_quantity;
    char *output_file;
} command_line_data;

// Funcoes uteis

void print_new_line()
{
    printf("\n");
}

command_line_data *get_input_data(int argc, char *argv[])
{
    command_line_data *command_line_data = malloc(sizeof(command_line_data));
    command_line_data->thread_number = atoi(argv[1]);

    int numbers_list_length = INITIAL_INPUT_NUMBERS_QUANTITY; // Valor inicial
    int numbers_count = 0;
    command_line_data->numbers = malloc(sizeof(int) * numbers_list_length);

    FILE *file;

    for (int i = 2; i < argc - 2; i++)
    {
        file = fopen(argv[i], "r");
        char file_line[MAX_FILE_LINE_LENGTH];

        while (fgets(file_line, MAX_FILE_LINE_LENGTH, file))
        {
            int number = atoi(file_line);

            if (numbers_count == numbers_list_length)
            {
                numbers_list_length *= 1.5;
                command_line_data->numbers = realloc(command_line_data->numbers, sizeof(int) * numbers_list_length);
            }

            command_line_data->numbers[numbers_count++] = number;
        }
    }

    command_line_data->numbers_quantity = numbers_count;
    command_line_data->output_file = argv[argc - 1];

    return command_line_data;
}

void print_numbers(int *numbers, int length)
{
    for (int i = 0; i < length; i++)
        printf("%d ", numbers[i]);
}

int_group **divide_into_groups(int *numbers, int group_quantity, int group_length)
{
    int_group **groups = malloc(sizeof(int_group *) * group_quantity);

    for (int i = 0; i < group_quantity; i++)
    {
        groups[i] = malloc(sizeof(int_group));
        groups[i]->length = group_length;
        groups[i]->numbers = malloc(sizeof(int) * group_length);

        for (int j = 0; j < group_length; j++)
            groups[i]->numbers[j] = numbers[j + i * group_length];
    }

    return groups;
}

// Funcoes para ordenacao

void bubble_sort(int *numbers, int length)
{
    for (int i = length - 1; i > 0; i--)
        for (int j = 0; j < i; j++)
            if (numbers[j] > numbers[j + 1])
            {
                int temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
}

int_group *merge_two_groups(int_group *a, int_group *b)
{
    int result_length = (a->length + b->length);
    int *result = malloc(sizeof(int) * result_length);

    int a_index = 0, b_index = 0, result_index = 0;
    while (a_index < a->length && b_index < b->length)
    {
        if (a->numbers[a_index] <= b->numbers[b_index])
            result[result_index++] = a->numbers[a_index++];
        else
            result[result_index++] = b->numbers[b_index++];
    }

    while (a_index < a->length)
        result[result_index++] = a->numbers[a_index++];

    while (b_index < b->length)
        result[result_index++] = b->numbers[b_index++];

    int_group *group = malloc(sizeof(int_group));
    group->numbers = result;
    group->length = result_length;

    return group;
}

int_group *merge_groups(int_group **groups, int group_quantity, int group_length)
{
    int_group *temp_group = malloc(sizeof(int_group));
    temp_group->numbers = groups[0]->numbers;
    temp_group->length = group_length;

    for (int i = 1; i < group_quantity; i++)
        temp_group = merge_two_groups(temp_group, groups[i]);

    return temp_group;
}

// Funcoes para thread

void *thread_func(void *arg)
{
    int_group *group = (int_group *)arg;
    bubble_sort(group->numbers, group->length);

    pthread_exit(NULL); // Verificar necessidade
}

int main(int argc, char *argv[])
{
    command_line_data *command_line_data = get_input_data(argc, argv);
    int *numbers = command_line_data->numbers;
    int numbers_quantity = command_line_data->numbers_quantity;
    int thread_number = command_line_data->thread_number;
    int group_length = numbers_quantity / thread_number;

    pthread_t threads[thread_number];
    int_group **groups = divide_into_groups(numbers, thread_number, group_length);

    for (int i = 0; i < thread_number; i++)
        pthread_create(&threads[i], NULL, thread_func, groups[i]);

    for (int i = 0; i < thread_number; i++)
        pthread_join(threads[i], NULL);

    printf("Agrupamentos obtidos apos resolucao de threads:\n");

    for (int i = 0; i < thread_number; i++)
    {
        printf("-> Agrupamento %d: ", (i + 1));
        print_numbers(groups[i]->numbers, group_length);
        print_new_line();
    }

    int_group *sorted_all_groups = merge_groups(groups, thread_number, group_length);

    printf("Antes da ordenacao: ");
    print_numbers(numbers, numbers_quantity);
    printf("\nDepois da ordenacao: ");
    print_numbers(sorted_all_groups->numbers, sorted_all_groups->length);
    print_new_line();

    return 0;
}