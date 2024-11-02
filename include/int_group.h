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
 * Mescla um vetor de grupos de inteiros num unico grupo de inteiros, mantendo ordenacao
 * @param groups vetor de grupos de inteiros
 * @param group_quantity quantidade de grupos de inteiros no vetor
 * @return grupo unico de inteiros
 */
int_group *merge_groups(int_group **groups, int group_quantity);

/**
 * Ordena um grupo de inteiros utilizando algoritmo quick sort
 * @param group grupo de inteiros a ser ordenado
 */
void sort_group(int_group *group);

#endif
