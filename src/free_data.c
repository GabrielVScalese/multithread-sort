#include <stdlib.h>
#include "../include/int_group.h"
#include "../include/io_utils.h"
#include "../include/thread_utils.h"

void free_input_data(input_data *data) {
    if (data) { 
        for (int i = 0; i < data->files_quantity; i++) {
            free(data->file_names[i]);
        }
        free(data);
    }
}

void free_int_group_double_pointer(int_group **data) {
    if (data && *data) { 
        free((*data)->numbers);
        free((*data));
    }
}

void free_int_group(int_group *data) {
    if (data) { 
        free(data);
    }
}

void free_thread_data_double_pointer(thread_data **data) {
    if (data && *data) { 
        for (int i = 0; i < (*data)->files_quantity; i++) {
            free((*data)->file_names[i]);
        }
        free((*data));
    }
}