#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <getopt.h>

#define MAX_FILE_LINE_LENGTH 100
#define INITIAL_INPUT_NUMBERS_QUANTITY 10

// Tipos

typedef struct int_list
{
    int *numbers;
    int length;
} int_list;

typedef struct command_line_data
{
    int thread_number;
    int *numbers;
    int numbers_quantity;
    char *output_file;
} command_line_data;

int thread_number;
int group_length;

// Funcoes uteis

void print_new_line()
{
    printf("\n");
}

command_line_data *get_input_data(int argc, char *argv[])
{
    command_line_data *command_line_data = malloc(sizeof(command_line_data));
    command_line_data->thread_number = atoi(argv[1]);

    int numbers_size = INITIAL_INPUT_NUMBERS_QUANTITY; // Valor inicial
    int numbers_count = 0;
    command_line_data->numbers = malloc(sizeof(int) * numbers_size);

    for (int i = 2; i < argc - 2; i++)
    {
        FILE *file = fopen(argv[i], "r");
        char file_line[MAX_FILE_LINE_LENGTH];

        if (numbers_count == numbers_size)
            command_line_data->numbers = realloc(command_line_data->numbers, numbers_size * 2);

        while (fgets(file_line, MAX_FILE_LINE_LENGTH, file))
        {
            int number;
            sscanf(file_line, "%d", &number);
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

int **create_matrix(int row, int column)
{
    int **matrix = (int **)malloc(sizeof(int *) * row);
    for (int i = 0; i < row; i++)
        matrix[i] = (int *)malloc(sizeof(int) * column);

    return matrix;
}

int **divide_into_groups(int *numbers)
{
    int **groups = create_matrix(thread_number, group_length);

    for (int i = 0; i < thread_number; i++)
        for (int k = 0; k < group_length; k++)
            groups[i][k] = numbers[k + i * group_length];

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

int_list *merge_two_groups(int *a, int a_length, int *b, int b_length)
{
    int result_length = (a_length + b_length);
    int *result = malloc(sizeof(int) * result_length);
    int a_index = 0, b_index = 0, result_index = 0;
    while (a_index < a_length && b_index < b_length)
    {
        if (a[a_index] <= b[b_index])
            result[result_index++] = a[a_index++];
        else
            result[result_index++] = b[b_index++];
    }

    while (a_index < a_length)
        result[result_index++] = a[a_index++];

    while (b_index < b_length)
        result[result_index++] = b[b_index++];

    int_list *list = malloc(sizeof(int_list));
    list->numbers = result;
    list->length = result_length;

    return list;
}

int *merge_groups(int **groups)
{
    int_list *temp_list = malloc(sizeof(int_list));
    temp_list->numbers = groups[0];
    temp_list->length = group_length;

    for (int i = 1; i < thread_number; i++)
        temp_list = merge_two_groups(temp_list->numbers, temp_list->length, groups[i], group_length);

    return temp_list->numbers;
}

// Funcoes para thread

void *thread_func(void *arg)
{
    int *numbers = (int *)arg;
    bubble_sort(numbers, group_length);

    pthread_exit(NULL); // Verificar necessidade
}

int main(int argc, char *argv[])
{
    int numbers[16] = {4, 3, 6, 9, 1, 7, 45, 21, 67, 13, 43, 12, 89, 2, 3, 0};

    thread_number = 4;
    group_length = 16 / thread_number;
    pthread_t threads[thread_number];

    int **groups = divide_into_groups(numbers);

    for (int i = 0; i < thread_number; i++)
        pthread_create(&threads[i], NULL, thread_func, groups[i]);

    for (int i = 0; i < thread_number; i++)
        pthread_join(threads[i], NULL);

    printf("Agrupamentos obtidos apos resolucao de threads:\n");

    for (int i = 0; i < thread_number; i++)
    {
        printf("-> Agrupamento %d: ", (i + 1));
        print_numbers(groups[i], group_length);
        print_new_line();
    }

    int *sorted_numbers = merge_groups(groups);

    printf("Antes da ordenacao: ");
    print_numbers(numbers, 16);
    printf("\nDepois da ordenacao: ");
    print_numbers(sorted_numbers, 16);
    print_new_line();

    return 0;
}