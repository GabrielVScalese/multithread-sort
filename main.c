#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>

// Constantes

#define MAX_FILE_LINE_LENGTH 100
#define INITIAL_NUMBERS_LIST_LENGTH 10

// Tipos

typedef struct int_group
{
    int *numbers;
    int length;
} int_group;

typedef struct thread_data
{
    int thread_number;
    int_group *group;
} thread_data;

typedef struct input_data
{
    int thread_number;
    int *numbers;
    int numbers_quantity;
    char *output_file;
} input_data;

// Funcoes uteis

void print_numbers(int *numbers, int length)
{
    for (int i = 0; i < length; i++)
        printf("%d ", numbers[i]);
}

void print_new_line()
{
    printf("\n");
}

// Funcoes para lidar com leitura e escrita de dados

input_data *get_input_data(int argc, char *argv[])
{
    input_data *input_data = malloc(sizeof(input_data));
    input_data->thread_number = atoi(argv[1]);

    int numbers_list_length = INITIAL_NUMBERS_LIST_LENGTH;
    int numbers_count = 0;
    input_data->numbers = malloc(sizeof(int) * numbers_list_length);

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

void write_output_data(int_group *group, char *output_file)
{
    FILE *file = fopen(output_file, "w");
    for (int i = 0; i < group->length; i++)
        if (i != group->length - 1)
            fprintf(file, "%d\n", group->numbers[i]);
        else
            fprintf(file, "%d", group->numbers[i]);

    fclose(file);
}

// Funcoes para manejo de grupos de inteiros

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

int_group *merge_groups(int_group **groups, int group_quantity)
{
    int_group *temp_group = malloc(sizeof(int_group));
    temp_group->numbers = groups[0]->numbers;
    temp_group->length = groups[0]->length;

    for (int i = 1; i < group_quantity; i++)
        temp_group = merge_two_groups(temp_group, groups[i]);

    return temp_group;
}

// Funcao para ordencao de valores inteiros

void quick_sort(int *numbers, int start_pos, int end_pos)
{
    int pivot = numbers[start_pos];
    int left = start_pos;
    int right = end_pos;

    while (left <= right)
    {
        while (numbers[left] < pivot)
            left++;
        while (numbers[right] > pivot)
            right--;

        if (left <= right)
        {
            int temp = numbers[left];
            numbers[left] = numbers[right];
            numbers[right] = temp;
            left++;
            right--;
        }
    }

    if (start_pos < right)
        quick_sort(numbers, start_pos, right);
    if (left < end_pos)
        quick_sort(numbers, left, end_pos);
}

// Funcao para thread

void *thread_func(void *arg)
{
    thread_data *thread_data = arg;
    clock_t time;

    time = clock();
    quick_sort(thread_data->group->numbers, 0, thread_data->group->length - 1);
    time = clock() - time;

    double thread_time = ((double)time / CLOCKS_PER_SEC);
    printf("Tempo de execucao do Thread %i: %f segundos.", thread_data->thread_number, thread_time);
    print_new_line();
}

int main(int argc, char *argv[])
{
    input_data *input_data = get_input_data(argc, argv);
    int *numbers = input_data->numbers;
    int numbers_quantity = input_data->numbers_quantity;
    int thread_number = input_data->thread_number;
    char *output_file = input_data->output_file;
    int group_length = numbers_quantity / thread_number;

    pthread_t threads[thread_number];
    thread_data **thread_datas = malloc(sizeof(thread_data *) * thread_number);
    int_group **groups = divide_into_groups(numbers, thread_number, group_length);

    clock_t time = clock();
    for (int i = 0; i < thread_number; i++)
    {
        thread_datas[i] = malloc(sizeof(thread_data));
        thread_datas[i]->thread_number = i;
        thread_datas[i]->group = groups[i];
        pthread_create(&threads[i], NULL, thread_func, thread_datas[i]);
    }

    for (int i = 0; i < thread_number; i++)
        pthread_join(threads[i], NULL);

    time = clock() - time;
    double all_threads_time = (double)time / CLOCKS_PER_SEC;
    printf("Tempo total de execução: %f segundos.", all_threads_time);
    print_new_line();

    int_group *sorted_all_groups = merge_groups(groups, thread_number);
    write_output_data(sorted_all_groups, output_file);

    return 0;
}