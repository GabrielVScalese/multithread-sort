#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include "../include/int_group.h"
#include "../include/io_utils.h"

typedef struct thread_data {
    int thread_number;
    int_group *group;
} thread_data;

void *thread_func(void *arg) {
    thread_data *thread_data = arg;
    clock_t time;

    time = clock();
    sort_group(thread_data->group);
    time = clock() - time;

    double thread_time = ((double) time / CLOCKS_PER_SEC);
    printf("Tempo de execucao do Thread %i: %f segundos.", thread_data->thread_number, thread_time);
    print_new_line();
}

int main(int argc, char *argv[]) {
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
    for (int i = 0; i < thread_number; i++) {
        thread_datas[i] = malloc(sizeof(thread_data));
        thread_datas[i]->thread_number = i;
        thread_datas[i]->group = groups[i];
        pthread_create(&threads[i], NULL, thread_func, thread_datas[i]);
    }

    for (int i = 0; i < thread_number; i++)
        pthread_join(threads[i], NULL);

    time = clock() - time;
    double all_threads_time = (double) time / CLOCKS_PER_SEC;
    printf("Tempo total de execução: %f segundos.", all_threads_time);
    print_new_line();

    int_group *sorted_all_groups = merge_groups(groups, thread_number);
    write_output_data(sorted_all_groups, output_file);

    return 0;
}
