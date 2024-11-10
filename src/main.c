#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/int_group.h"
#include "../include/io_utils.h"
#include "../include/thread_utils.h"

/**
 * Cada thread devera ler numeros inteiros de um certo numero de arquivos, ordena-los num grupo de inteiros e calcular/printar tempo gasto para isso
 * @param arg dados sobre numero de threads, quantidade de arquivos a serem lidos, nomes de arquivos a serem lidos e arquivo de saida
 * @return nao ha retorno
 */
void *thread_func(void *arg) {
    thread_data *thread_data = arg;
    thread_data->group = malloc(sizeof(int_group));
    thread_data->group->numbers = malloc(sizeof(int) * INITIAL_GROUP_LENGTH);
    thread_data->group->length = 0;

    for (int i = 0; i < thread_data->files_quantity; i++)
        read_numbers_from_file(thread_data->file_names[i], thread_data->group);

    clock_t time = clock();
    sort_group(thread_data->group);
    time = clock() - time;

    double thread_time = ((double) time / CLOCKS_PER_SEC);
    printf("Tempo de execucao do Thread %i: %f segundos.\n", thread_data->thread_number, thread_time);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    input_data *input_data = get_input_data(argc, argv);
    char *output_file = input_data->output_file;

    int threads_to_create_quantity;
    if (input_data->files_quantity < input_data->thread_quantity)
        threads_to_create_quantity = input_data->files_quantity;
    else
        threads_to_create_quantity = input_data->thread_quantity;

    thread_data **thread_datas = create_thread_datas(input_data->files_quantity, input_data->file_names,
                                                     threads_to_create_quantity);

    pthread_t threads[threads_to_create_quantity];

    clock_t time = clock();
    for (int i = 0; i < threads_to_create_quantity; i++)
        pthread_create(&threads[i], NULL, thread_func, thread_datas[i]);

    for (int i = 0; i < threads_to_create_quantity; i++)
        pthread_join(threads[i], NULL);
    time = clock() - time;

    double all_threads_time = (double) time / CLOCKS_PER_SEC;
    printf("Tempo total de execucao: %f segundos.\n", all_threads_time);

    int_group **joined_thread_groups = malloc(sizeof(int_group *) * threads_to_create_quantity);
    for (int i = 0; i < threads_to_create_quantity; i++)
        joined_thread_groups[i] = thread_datas[i]->group;

    int_group *sorted_all_groups = merge_groups(joined_thread_groups, threads_to_create_quantity);
    write_output_data(sorted_all_groups, output_file);

    return 0;
}
