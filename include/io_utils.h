#ifndef IO_UTILS_H
#define IO_UTILS_H

#include "../include/int_group.h"

/**
* Tamanho maximo de um nome de arquivo
*/
#define FILE_NAME_LENGTH 100

/**
 * Tamanho maximo de uma linha de um arquivo de entrada
 */
#define MAX_FILE_LINE_LENGTH 100

/**
 * Numero inicial de elementos de um vetor de inteiros (usado durante leitura de arquivos contendo inteiros)
 */
#define INITIAL_GROUP_LENGTH 10

/**
 * Valor limite para redimencionar vetor de inteiros (usado durante leitura de arquivos contendo inteiros)
 */
#define RESIZE_THRESHOLD 1.5

/**
 * Estrutura para armazenar: numero de threads, quantidade de arquivos a serem lidos, nomes de arquivos a serem lidos e arquivo de saida
 */
typedef struct input_data {
 int thread_quantity;
 int files_quantity;
 char **file_names;
 char *output_file;
} input_data;

/**
 * Realiza a leitura dos argumentos passados ao programa
 * @param argc quantidade de argumentos passados ao programa
 * @param argv valores fornecidos como argumentos ao programa
 * @return estrutura contendo: numero de threads, quantidade de arquivos a serem lidos, nomes de arquivos a serem lidos e arquivo de saida
 */
input_data *get_input_data(int argc, char *argv[]);

/**
 * Escreve no arquivo de saida especificado todos os inteiros ordenados de maneira crescente
 * @param group grupo de inteiros ordenados
 * @param output_file arquivo onde vai ser feita a escrita
 */
void write_output_data(int_group *group, char *output_file);

void read_numbers_from_file(char *file_name, int_group *group);

#endif
