#include <stdlib.h>
#include <string.h>
#include "../include/thread_utils.h"
#include "../include/io_utils.h"

thread_data **create_thread_datas(int files_quantity, char **file_names, int thread_quantity) {
    thread_data **thread_datas = malloc(sizeof(thread_data *) * thread_quantity);
    if(!thread_datas) {
        printf("Erro: alocacao de memoria (thread_datas)\n");
        pthread_exit(NULL);
    }

    int file_names_array_length = INITIAL_FILE_NAMES_ARRAY_LENGTH;
    for (int j = 0, i = 0; j < files_quantity; j++, i++) {
        if (i == thread_quantity)
            i = 0;

        if (thread_datas[i] == NULL) {
            thread_datas[i] = malloc(sizeof(thread_data));
            if(!thread_datas[i]) {
                printf("Erro: alocacao de memoria (thread_data[%d])\n", i);
                pthread_exit(NULL);
            }
            thread_datas[i]->file_names = malloc(sizeof(char *) * INITIAL_FILE_NAMES_ARRAY_LENGTH);
            if(!thread_datas[i]->file_names) {
                printf("Erro: alocacao de memoria (thread_data[%d]->file_names)\n", i);
                pthread_exit(NULL);
            }
            thread_datas[i]->thread_number = i;
            thread_datas[i]->files_quantity = 0;
        }

        if (thread_datas[i]->files_quantity == file_names_array_length) {
            file_names_array_length = thread_datas[i]->files_quantity + 1;
            thread_datas[i]->file_names = realloc(thread_datas[i]->file_names,
                                                  sizeof(char *) * file_names_array_length);
            if(!thread_datas[i]->file_names) {
                printf("Erro: alocacao de memoria (thread_data[%d]->file_names)\n", i);
                pthread_exit(NULL);
            }
        }

        thread_datas[i]->file_names[thread_datas[i]->files_quantity] = malloc(sizeof(char) * FILE_NAME_LENGTH);
        if(!thread_datas[i]->file_names[thread_datas[i]->files_quantity]) {
            printf("Erro: alocacao de memoria (thread_data[%d]->file_names[thread_datas[%d]->files_quantity])\n", i, i);
            pthread_exit(NULL);
        }
        strcpy(thread_datas[i]->file_names[thread_datas[i]->files_quantity], file_names[j]);
        thread_datas[i]->files_quantity++;
    }

    return thread_datas;
}