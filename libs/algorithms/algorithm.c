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

void insertionSort(int *a, size_t size) {
    for (long long i = 1; i < size; i++) {
        int temp = a[i];
        long long j = i - 1;

        while (j > -1 && a[j] > temp) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = temp;
    }
}

void combSort(int *a, size_t size) {
    size_t step = size;
    bool swapped = true;
    while (step > 1 || swapped) {
        if (step > 1) {
            step /= 1.24733;
        }

        swapped = false;
        for (size_t i = 0, j = i + step; j < size; ++ i, ++ j) {
            if (a[i] > a[j]) {
                swap(&a[i], &a[j]);
                swapped = true;
            }
        }
    }
}