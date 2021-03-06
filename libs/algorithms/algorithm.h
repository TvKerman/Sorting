//
// Created by Григорий on 01.02.2022.
//

#ifndef COURSE_ALGORITHM_H
#define COURSE_ALGORITHM_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b);

int min2(int a, int b);

void exchangeSort(int *a, size_t size);

void selectionSort(int *a, size_t size);

void insertionSort(int *a, size_t size);

void combSort(int *a, size_t size);

void shellSort(int *a, size_t size);

void digitalSort(int *a, size_t size);

void generateRandomArray(int *a, size_t size);

void generateOrderedArray(int *a, size_t size);

void generateOrderedBackwards(int *a, size_t size);

long long getExchangeSortNComp(int *a, size_t size);

long long getSelectionSortNComp(int *a, size_t size);

long long getInsertionSortNComp(int *a, size_t size);

long long getCombSortNComp(int *a, size_t size);

long long getShellSortNComp(int *a, size_t size);

long long getDigitalSortNComp(int *a, size_t size);

#endif //COURSE_ALGORITHM_H
