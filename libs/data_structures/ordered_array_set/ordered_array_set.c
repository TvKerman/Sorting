//
// Created by Григорий on 01.02.2022.
//

#include "ordered_array_set.h"
#include <malloc.h>

static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

ordered_array_set ordered_array_set_create(size_t capacity) {
    return (ordered_array_set){malloc(capacity * sizeof(int)), 0, capacity};
}

ordered_array_set ordered_array_set_create_from_array(const int *a, size_t size) {
    ordered_array_set set = ordered_array_set_create(size);
    for (size_t i = 0; i < size; i++) {
        ordered_array_set_insert(&set, a[i]);
    }
    return set;
}

size_t ordered_array_set_in(ordered_array_set *set, int value) {
    size_t index = binarySearchMoreOrEqual_(set->data, set->size, value);
    if (set->data[index] == value) {
        return index;
    }
    return set->size;
}

bool ordered_array_set_isEqual(ordered_array_set set1, ordered_array_set set2) {
    if (set1.size != set2.size) {
        return false;
    }
    for (size_t i = 0; i < set1.size; i++) {
        if (set1.data[i] != set2.data[i]) {
            return false;
        }
    }
    return true;
}

bool ordered_array_set_isSubset(ordered_array_set subset, ordered_array_set set) {
    if (subset.size > set.size) {
        return false;
    }
    for (size_t i = 0; i < subset.size; i++) {
        if (ordered_array_set_in(&set, subset.data[i]) == set.size) {
            return false;
        }
    }
    return true;
}

void ordered_array_set_isAbleAppend(ordered_array_set *set) {
    assert(set->size < set->capacity);
}

void ordered_array_set_insert(ordered_array_set *set, int value) {
    if (ordered_array_set_in(set, value) == set->size) {
        ordered_array_set_isAbleAppend(set);
        for (size_t i = 0; i < set->size; i++) {
            if (set->data[i] > value) {
                swap(&set->data[i], &value);
            }
        }
        append_(set->data, &set->size, value);
    }
}

void ordered_array_set_deleteElement(ordered_array_set *set, int value) {
    size_t index = ordered_array_set_in(set, value);
    if (index != set->size) {
        set->size--;
        for (size_t i = index; i < set->size; i++) {
            set->data[i] = set->data[i + 1];
        }
    }
}

ordered_array_set ordered_array_set_union(ordered_array_set set1, ordered_array_set set2) {
    ordered_array_set set = ordered_array_set_create(set1.size + set2.size);

    size_t index1 = 0;
    size_t index2 = 0;
    while (index1 < set1.size && index2 < set2.size) {
        if (set1.data[index1] < set2.data[index2]) {
            append_(set.data, &set.size, set1.data[index1++]);
        } else if (set2.data[index2] < set1.data[index1]) {
            append_(set.data, &set.size, set2.data[index2++]);
        } else {
            append_(set.data, &set.size, set1.data[index1++]);
            index2++;
        }
    }

    while (index1 < set1.size) {
        append_(set.data, &set.size, set1.data[index1++]);
    }
    while (index2 < set2.size) {
        append_(set.data, &set.size, set2.data[index2++]);
    }
    //for (size_t i = 0; i < set1.size; i++) {
    //    append_(set.data, &set.size, set1.data[i]);
    //}
    //for (size_t i = 0; i < set2.size; i++) {
    //    ordered_array_set_insert(&set, set2.data[i]);
    //}
    return set;
}

ordered_array_set ordered_array_set_intersection(ordered_array_set set1, ordered_array_set set2) {
    ordered_array_set set = ordered_array_set_create(set1.size);

    size_t index1 = 0;
    size_t index2 = 0;
    while (index1 < set1.size && index2 < set2.size) {
        if (set1.data[index1] < set2.data[index2]) {
            index1++;
        } else if (set2.data[index2] < set1.data[index1]) {
            index2++;
        } else {
            append_(set.data, &set.size, set1.data[index1++]);
            index2++;
        }
    }
    //for (size_t i = 0; i < set1.size; i++) {
    //    if (ordered_array_set_in(&set2, set1.data[i]) != set2.size) {
    //        append_(set.data, &set.size, set1.data[i]);
    //    }
    //}
    return set;
}

ordered_array_set ordered_array_set_difference(ordered_array_set set1, ordered_array_set set2) {
    ordered_array_set set = ordered_array_set_create(set1.size);

    size_t index1 = 0;
    size_t index2 = 0;
    while (index1 < set1.size && index2 < set2.size) {
        if (set1.data[index1] < set2.data[index2]) {
            append_(set.data, &set.size, set1.data[index1++]);
        } else if (set2.data[index2] < set1.data[index1]) {
            index2++;
        } else {
            index1++;
            index2++;
        }
    }

    while (index1 < set1.size) {
        append_(set.data, &set.size, set1.data[index1++]);
    }

    //for (size_t i = 0; i < set1.size; i++) {
    //    if (ordered_array_set_in(&set2, set1.data[i]) == set2.size) {
    //        append_(set.data, &set.size, set1.data[i]);
    //    }
    //}
    return set;
}

ordered_array_set ordered_array_set_symmetricDifference(ordered_array_set set1, ordered_array_set set2) {
    ordered_array_set set = ordered_array_set_create(set1.size + set2.size);

    size_t index1 = 0;
    size_t index2 = 0;
    while (index1 < set1.size && index2 < set2.size) {
        if (set1.data[index1] < set2.data[index2]) {
            append_(set.data, &set.size, set1.data[index1++]);
        } else if (set2.data[index2] < set1.data[index1]) {
            append_(set.data, &set.size, set2.data[index2++]);
        } else {
            index1++;
            index2++;
        }
    }

    while (index1 < set1.size) {
        append_(set.data, &set.size, set1.data[index1++]);
    }
    while (index2 < set2.size) {
        append_(set.data, &set.size, set2.data[index2++]);
    }

    //for (size_t i = 0; i < set1.size; i++) {
    //    if (ordered_array_set_in(&set2, set1.data[i]) == set2.size) {
    //        append_(set.data, &set.size, set1.data[i]);
    //    }
    //}
    //for (size_t i = 0; i < set2.size; i++) {
    //    if (ordered_array_set_in(&set1, set2.data[i]) == set1.size) {
    //        ordered_array_set_insert(&set, set2.data[i]);
    //    }
    //}
    return set;
}

ordered_array_set ordered_array_set_complement(ordered_array_set set, ordered_array_set universumSet) {
    assert(ordered_array_set_isSubset(set, universumSet));
    return ordered_array_set_difference(universumSet, set);
}

void ordered_array_set_print(ordered_array_set set) {
    printf("{");
    for (size_t i = 0; i < set.size; i++) {
        printf("%d, ", set.data[i]);
    }
    if (set.size == 0) {
        printf("}\n");
    } else {
        printf("\b\b}\n");
    }
}

void ordered_array_set_delete(ordered_array_set *set) {
    if (set->size != 0) {
        free(set->data);
        set->size = 0;
        set->capacity = 0;
    }
}
