#include "../include/int_group.h"
#include "../include/io_utils.h"
#include "../include/thread_utils.h"

void free_input_data(input_data *data) {
    if (data) { 
        for (int i = 0; i < data->files_quantity; i++) {
            free(data->file_names[i]);
        }

        free(data->file_names);
        free(data->output_file);
        free(data);
    }
}

void free_int_group(int_group *data) {
    if (data) { 
        for (int i = 0; i < data->length; i++) {
            free(data->numbers[i]);
        }

        free(data->numbers);
        free(data);
    }
}

void free_thread_data(thread_data *data) {
    if (data) { 
        for (int i = 0; i < data->files_quantity; i++) {
            free(data->file_names[i]);
        }

        free_int_group(data->group);
        free(data);
    }
}