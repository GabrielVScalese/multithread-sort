#ifndef INT_GROUP_H
#define INT_GROUP_H

/**
 * Estrutura para armazenar um grupo de inteiros e quantidade de inteiros desse grupo
 */
typedef struct int_group {
 int *numbers;
 int length;
} int_group;

/**
 * Mescla dois grupos de inteiros ordenados de forma a obter um grupo ordenado
 * @param a grupo de inteiros ordenados (crescente)
 * @param b grupo de inteiros ordenados (crescente)
 * @return grupo de inteiros ordenados contendo a e b
 */
int_group *merge_two_groups(int_group *a, int_group *b);

/**
 * Mescla um vetor de grupos de inteiros num unico grupo de inteiros, mantendo ordenacao
 * @param groups vetor de grupos de inteiros
 * @param group_quantity quantidade de grupos de inteiros no vetor
 * @return grupo unico de inteiros
 */
int_group *merge_groups(int_group **groups, int group_quantity);

/**
 * Algoritmo de ordenacao de grupo de inteiros baseado no paradigma "dividir-e-conquistar"
 * @param group grupo de inteiros a ser ordenado
 * @param start_pos posicao inicial do grupo de inteiros
 * @param end_pos posicao final do grupo de inteiros
 */
void quick_sort(int_group *group, int start_pos, int end_pos);

/**
 * Ordena um grupo de inteiros utilizando algoritmo quick sort
 * @param group grupo de inteiros a ser ordenado
 */
void sort_group(int_group *group);

#endif
