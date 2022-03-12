//
// Created by Григорий on 01.02.2022.
//

#include "algorithm.h"

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void exchangeSorting(int *a, size_t size) {
    for (size_t i = 0; i < size; i++) {
        size_t countComparisons = size - i;
        for (size_t j = 1; j < countComparisons; j++) {
            if (a[j] < a[j - 1]) {
                swap(&a[j], &a[j - 1]);
            }
        }
    }
}