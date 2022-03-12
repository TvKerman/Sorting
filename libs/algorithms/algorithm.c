//
// Created by Григорий on 01.02.2022.
//

#include "algorithm.h"

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int min2(int a, int b) {
    return a < b ? a : b;
}

void exchangeSort(int *a, size_t size) {
    for (size_t i = 0; i < size; i++) {
        size_t countComparisons = size - i;
        for (size_t j = 1; j < countComparisons; j++) {
            if (a[j] < a[j - 1]) {
                swap(&a[j], &a[j - 1]);
            }
        }
    }
}

void selectionSort(int *a, size_t size) {
    for (size_t i = 0; i < size - 1; i++) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < size; j++) {
            if (a[minIndex] > a[j]) {
                minIndex = j;
            }
        }

        swap(&a[minIndex], &a[i]);
    }
}