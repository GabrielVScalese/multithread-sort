#include "../include/int_group.h"
#include <stdlib.h>

int_group **divide_into_groups(int *numbers, int group_quantity, int group_length) {
    int_group **groups = malloc(sizeof(int_group *) * group_quantity);
    for (int i = 0; i < group_quantity; i++) {
        groups[i] = malloc(sizeof(int_group));
        groups[i]->length = group_length;
        groups[i]->numbers = malloc(sizeof(int) * group_length);

        for (int j = 0; j < group_length; j++)
            groups[i]->numbers[j] = numbers[j + i * group_length];
    }

    return groups;
}

int_group *merge_two_groups(int_group *a, int_group *b) {
    int result_length = (a->length + b->length);
    int *result = malloc(sizeof(int) * result_length);

    int a_index = 0, b_index = 0, result_index = 0;
    while (a_index < a->length && b_index < b->length) {
        if (a->numbers[a_index] <= b->numbers[b_index])
            result[result_index++] = a->numbers[a_index++];
        else
            result[result_index++] = b->numbers[b_index++];
    }

    while (a_index < a->length)
        result[result_index++] = a->numbers[a_index++];

    while (b_index < b->length)
        result[result_index++] = b->numbers[b_index++];

    int_group *group = malloc(sizeof(int_group));
    group->numbers = result;
    group->length = result_length;

    return group;
}

int_group *merge_groups(int_group **groups, int group_quantity) {
    int_group *temp_group = malloc(sizeof(int_group));
    temp_group->numbers = groups[0]->numbers;
    temp_group->length = groups[0]->length;

    for (int i = 1; i < group_quantity; i++)
        temp_group = merge_two_groups(temp_group, groups[i]);

    return temp_group;
}

void quick_sort(int_group *group, int start_pos, int end_pos) {
    int pivot = group->numbers[start_pos];
    int left = start_pos;
    int right = end_pos;

    while (left <= right) {
        while (group->numbers[left] < pivot)
            left++;
        while (group->numbers[right] > pivot)
            right--;

        if (left <= right) {
            int temp = group->numbers[left];
            group->numbers[left] = group->numbers[right];
            group->numbers[right] = temp;
            left++;
            right--;
        }
    }

    if (start_pos < right)
        quick_sort(group, start_pos, right);
    if (left < end_pos)
        quick_sort(group, left, end_pos);
}

void sort_group(int_group *group) {
    quick_sort(group, 0, group->length - 1);
}
