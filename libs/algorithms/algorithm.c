//
// Created by Григорий on 01.02.2022.
//

#include "algorithm.h"
#include <malloc.h>
#include <memory.h>

#define BIT_IN_DISCHARGE 8
#define COUNT_COMBINATION_DISCHARGE 256
#define ICONIC_DISCHARGE 31

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

void shellSort(int *a, size_t size) {
    for (long long s = size / 2; s > 0; s /= 2) {
        for (long long i = s; i < size; i++) {
            long long j = i - s;
            while (j >= 0 && a[j] > a[j + s]) {
                swap(&a[j], &a[j + s]);
                j -= s;
            }
        }
    }
}

void digitalSorting(int *a, size_t size) {
    int countDischarge = sizeof(int);
    int currentDischarge = 0;

    int *b = (int *)malloc(sizeof(int) * size);

    while (countDischarge > 0) {
        int countPositive[COUNT_COMBINATION_DISCHARGE] = {0};
        int posPositive[COUNT_COMBINATION_DISCHARGE] = {0};

        int countNegative[COUNT_COMBINATION_DISCHARGE] = {0};
        int posNegative[COUNT_COMBINATION_DISCHARGE] = {0};

        for (int i = 0; i < size; i++) {
            int discharge = (a[i] >> (currentDischarge * BIT_IN_DISCHARGE)) & ((1 << BIT_IN_DISCHARGE) - 1);
            if (a[i] >> ICONIC_DISCHARGE) {
                countNegative[discharge] += 1;
            } else {
                countPositive[discharge] += 1;
            }
        }

        for (int i = 1; i < COUNT_COMBINATION_DISCHARGE; i++) {
            posNegative[i] = countNegative[i - 1] + posNegative[i - 1];
        }
        posPositive[0] = posNegative[COUNT_COMBINATION_DISCHARGE - 1] + countNegative[COUNT_COMBINATION_DISCHARGE - 1];
        for (int i = 1; i < COUNT_COMBINATION_DISCHARGE; i++) {
            posPositive[i] = countPositive[i - 1] + posPositive[i - 1];
        }

        for (int i = 0; i < size; i++) {
            int discharge = (a[i] >> (currentDischarge * BIT_IN_DISCHARGE)) & ((1 << BIT_IN_DISCHARGE) - 1);
            if (a[i] >> ICONIC_DISCHARGE) {
                b[posNegative[discharge]++] = a[i];
            } else {
                b[posPositive[discharge]++] = a[i];
            }
        }

        memcpy(a, b, size * sizeof(int));

        countDischarge -= 1;
        currentDischarge += 1;
    }

    free(b);
}