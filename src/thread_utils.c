#include <stdlib.h>
#include <string.h>
#include "../include/thread_utils.h"
#include "../include/io_utils.h"

thread_data **create_thread_datas(int files_quantity, char **file_names, int thread_quantity) {
    thread_data **thread_datas = malloc(sizeof(thread_data *) * thread_quantity);

    for (int j = 0, i = 0; j < files_quantity; j++, i++) {
        if (i == thread_quantity)
            i = 0;

        if (thread_datas[i] == NULL) {
            thread_datas[i] = malloc(sizeof(thread_data));
            thread_datas[i]->file_names = malloc(sizeof(char *) * INITIAL_FILE_NAMES_ARRAY_LENGTH);
            thread_datas[i]->thread_number = i;
            thread_datas[i]->files_quantity = 0;
        }

        if (sizeof(thread_datas[i]->file_names) < sizeof(char *) * thread_datas[i]->files_quantity + 1)
            thread_datas[i]->file_names = realloc(thread_datas[i]->file_names,
                                                  sizeof(char *) * (thread_datas[i]->files_quantity + 1));

        thread_datas[i]->file_names[thread_datas[i]->files_quantity] = malloc(sizeof(char) * FILE_NAME_LENGTH);
        strcpy(thread_datas[i]->file_names[thread_datas[i]->files_quantity], file_names[j]);
        thread_datas[i]->files_quantity++;
    }

    return thread_datas;
}
