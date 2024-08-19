#ifndef INT_GROUP_H
#define INT_GROUP_H

typedef struct int_group {
    int *numbers;
    int length;
} int_group;

int_group **divide_into_groups(int *numbers, int group_quantity, int group_length);

int_group *merge_two_groups(int_group *a, int_group *b);

int_group *merge_groups(int_group **groups, int group_quantity);

void sort_group(int_group *group);

void quick_sort(int_group *group, int start_pos, int end_pos);

#endif
