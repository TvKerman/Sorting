//
// Created by Григорий on 19.12.2021.
//

#include "unordered_array_set.h"
#include <malloc.h>

unordered_array_set unordered_array_set_create(size_t capacity) {
    return (unordered_array_set){malloc(sizeof(int) * capacity), 0, capacity};
}

size_t unordered_array_set_in(unordered_array_set *set, int value) {
    return linearSearch_(set->data, set->size, value);
}

void unordered_array_set_isAbleAppend(unordered_array_set *set) {
    assert(set->size < set->capacity);
}

bool unordered_array_set_isEqual(unordered_array_set set1, unordered_array_set set2) {
    if (set1.size != set2.size) {
        return false;
    }
    for (size_t i = 0; i < set1.size; i++) {
        if (unordered_array_set_in(&set1, set2.data[i]) == set1.size) {
            return false;
        }
    }
    return true;
}

void unordered_array_set_insert(unordered_array_set *set, int value) {
    if (unordered_array_set_in(set, value) == set->size) {
        unordered_array_set_isAbleAppend(set);
        append_(set->data, &set->size, value);
    }
}

unordered_array_set unordered_array_set_create_from_array(const int *a, size_t size) {
    unordered_array_set set = unordered_array_set_create(size);
    for (size_t i = 0; i < size; i++) {
        unordered_array_set_insert(&set, a[i]);
    }
    return set;
}

void unordered_array_set_deleteElement(unordered_array_set *set, int value) {
    size_t index = unordered_array_set_in(set, value);
    if (index != set->size) {
        set->data[index] = set->data[set->size - 1];
        set->size -= 1;
    }
}

unordered_array_set unordered_array_set_union(unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set set = unordered_array_set_create(set1.size + set2.size);
    for (size_t i = 0; i < set1.size; i++) {
        append_(set.data, &set.size, set1.data[i]);
    }
    for (size_t i = 0; i < set2.size; i++) {
        unordered_array_set_insert(&set, set2.data[i]);
    }
    return set;
}

unordered_array_set unordered_array_set_intersection(unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set set = unordered_array_set_create(set1.size);
    for (size_t i = 0; i < set1.size; i++) {
        if (unordered_array_set_in(&set2, set1.data[i]) != set2.size) {
            append_(set.data, &set.size, set1.data[i]);
        }
    }
    return set;
}

unordered_array_set unordered_array_set_difference(unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set set = unordered_array_set_create(set1.size);
    for (size_t i = 0; i < set1.size; i++) {
        if (unordered_array_set_in(&set2, set1.data[i]) == set2.size) {
            append_(set.data, &set.size, set1.data[i]);
        }
    }

    return set;
}

unordered_array_set unordered_array_set_symmetricDifference(unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set set = unordered_array_set_create(set1.size + set2.size);

    for (size_t i = 0; i < set1.size; i++) {
        if (unordered_array_set_in(&set2, set1.data[i]) == set2.size) {
            append_(set.data, &set.size, set1.data[i]);
        }
    }

    for (size_t i = 0; i < set2.size; i++) {
        if (unordered_array_set_in(&set1, set2.data[i]) == set1.size) {
            append_(set.data, &set.size, set2.data[i]);
        }
    }
    return set;
}

bool unordered_array_set_isSubset(unordered_array_set subset, unordered_array_set set) {
    if (set.size < subset.size) {
        return false;
    }
    for (size_t i = 0; i < subset.size; i++) {
        if (unordered_array_set_in(&set, subset.data[i]) == set.size) {
            return false;
        }
    }
    return true;
}

unordered_array_set unordered_array_set_complement(unordered_array_set set, unordered_array_set universumSet) {
    assert(unordered_array_set_isSubset(set, universumSet));
    unordered_array_set set1 = unordered_array_set_difference(universumSet, set);
    //for (size_t i = 0; i < universumSet.size; i++) {
    //    if (unordered_array_set_in(&set, universumSet.data[i]) == set.size) {
    //        append_(set1.data, &set1.size, universumSet.data[i]);
    //    }
    //}
    return set1;
}

void unordered_array_set_print(unordered_array_set set) {
    printf("{");
    bool isEmpty = true;
    for (size_t i = 0; i < set.size; i++) {
        printf("%d, ", set.data[i]);
        isEmpty = false;
    }
    if (isEmpty) {
        printf("}\n");
    } else {
        printf("\b\b}\n");
    }
}

void unordered_array_set_delete(unordered_array_set *set) {
    if (set->size != 0) {
        free(set->data);
        set->size = 0;
        set->capacity = 0;
    }
}
