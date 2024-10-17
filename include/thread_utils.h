#ifndef THREAD_UTILS_H
#define THREAD_UTILS_H

#include "int_group.h"

/**
 * Numero inicial do tamanho do array de nomes de arquivos
 */
#define INITIAL_FILE_NAMES_ARRAY_LENGTH 2

/**
 * Estrutura para armazenar informacoes relevantes de uma thread: numero de threads, quantidade de arquivos a serem lidos, nomes de arquivos a serem lidos e arquivo de saida
 */
typedef struct thread_data {
 int thread_number;
 int files_quantity;
 char **file_names;
 int_group *group;
} thread_data;

/**
 * Divide os dados obtidos pelo input em estruturas a serem usadas nas threads
 * @param files_quantity quantidade de arquivos a serem lidos
 * @param file_names nomes dos arquivos a serem lidos
 * @param thread_quantity quantidade de threads a serem criadas
 * @return vetor de dados de threads
 */
thread_data **create_thread_datas(int files_quantity, char **file_names, int thread_quantity);

#endif //THREAD_UTILS_H
