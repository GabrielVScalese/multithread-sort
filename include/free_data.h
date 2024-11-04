#ifndef FREE_DATA_H
#define FREE_DATA_H

/**
 * Libera a alocacao de memoria do tipo de dado input_data (struct)
 * @param data grupo de dados que serao liberados da memoria
 */
void free_input_data(input_data *data);

/**
 * Libera a alocacao de memoria do tipo de dado int_group (struct)
 * @param data grupo de dados que serao liberados da memoria
 */
void free_int_group_double_pointer(int_group **data);
void free_int_group(int_group *data);

/**
 * Libera a alocacao de memoria do tipo de dado thread_data (struct)
 * @param data grupo de dados que serao liberados da memoria
 */
void free_thread_data_double_pointer(thread_data **data);
#endif


