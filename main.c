#include <stdlib.h >
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "libs/algorithms/algorithm.h"
#include "libs/algorithms/array/array.h"

#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])

#define TIME_TEST(testCode, time) { \
    clock_t start_time = clock(); \
    testCode \
    clock_t end_time = clock();\
    clock_t sort_time = end_time - start_time; \
    time = (double) sort_time / CLOCKS_PER_SEC; \
}

bool isOrdered(const int *a, size_t size) {
    for (size_t i = 1; i < size; i++) {
        if (a[i - 1] > a[i]) {
            return false;
        }
    }

    return true;
}

// функция сортировки
typedef struct SortFunc {
    void (*sort)(int *a, size_t n); // указатель на функцию сортировки
    char name[64]; // имя сортировки, используемое при выводе
}SortFunc;

// функция сортировки
typedef struct SortFuncNComps {
    long long (*sort)(int *a, size_t n); // указатель на функцию сортировки
    char name[64]; // имя сортировки, используемое при выводе
}SortFuncNComps;


// функция генерации
typedef struct GeneratingFunc {
    void (*generate) (int *a, size_t n); // указатель на функцию генерации последоват.
    char name[64]; // имя генератора, используемое при выводе
}GeneratingFunc;


double getTime () {
    clock_t start_time = clock ();
    // фрагмент кода
    // время которого измеряется
    clock_t end_time = clock ();
    clock_t sort_time = end_time - start_time;
    return  (double) sort_time / CLOCKS_PER_SEC;
}

void checkTime(void (*sortFunc)(int *, size_t), void (*generateFunc)(int *, size_t), size_t size, char *experimentName) {
    static size_t runCounter = 1;

    // генерация последовательности
    static int innerBuffer[20000000];
    generateFunc(innerBuffer, size);
    printf("Run #%zu| ", runCounter++);
    printf("Name: %s\n", experimentName);

    // замер времени
    double time;
    TIME_TEST({sortFunc(innerBuffer, size);}, time);

    // результаты замера
    printf (" Status : ") ;
    if (isOrdered(innerBuffer, size)) {
        printf ("OK! Time : %.3f s.\n", time);

        // запись в файл
        char filename [256];
        sprintf(filename, "./data/%s.csv", experimentName);
        FILE *f = fopen(filename, "a");
        if (f == NULL) {
            printf (" FileOpenError %s", filename);
            exit(1);
        }
        fprintf(f, "%zu; %.3f\n", size, time);
        fclose(f);
        } else {
        printf(" Wrong !\n");

        // вывод массива, который не смог быть отсортирован
        outputArray_(innerBuffer, size);

        exit(1);
        }
}

void timeExperimentSlowSorting() {
    // описание функций сортировки
    SortFunc sorts [] = {
            {exchangeSort, "exchangeSort"},
            {selectionSort, "selectionSort"},
            {insertionSort, "insertionSort"},
            {combSort, "combSort"},
            {shellSort, "shellSort"},
            {digitalSort, "digitalSort"}
            //{ selectionSort , " selectionSort "} ,
            //{ insertionSort , " insertionSort "} ,
            // вы добавите свои сортировки
            };
    const unsigned FUNCS_N = ARRAY_SIZE(sorts);

    // описание функций генерации
    GeneratingFunc generatingFuncs [] = {
            // генерируется случайный массив
            {generateRandomArray, "random"},
            // генерируется массив 0, 1, 2, ..., n - 1
            {generateOrderedArray, "ordered"},
            // генерируется массив n - 1, n - 2, ..., 0
            {generateOrderedBackwards, "orderedBackwards"}
            };
    const unsigned CASES_N = ARRAY_SIZE(generatingFuncs);

    // запись статистики в файл
    for (size_t size = 10000; size <= 100000; size += 10000) {
        printf (" - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        printf (" Size : %d\n", size);
        for (int i = 0; i < FUNCS_N ; i++) {
            for (int j = 0; j < CASES_N ; j++) {
                // генерация имени файла
                char filename[128];
                sprintf(filename, "%s_%s_time", sorts[i].name, generatingFuncs[j].name);
                checkTime(sorts[i].sort, generatingFuncs[j].generate, size, filename);
            }
        }
        printf ("\n") ;
    }
}

void timeExperimentQuickSorting() {
    // описание функций сортировки
    SortFunc sorts [] = {
            {combSort, "combSort"},
            {shellSort, "shellSort"},
            {digitalSort, "digitalSort"}
            //{ selectionSort , " selectionSort "} ,
            //{ insertionSort , " insertionSort "} ,
            // вы добавите свои сортировки
    };
    const unsigned FUNCS_N = ARRAY_SIZE(sorts);

    // описание функций генерации
    GeneratingFunc generatingFuncs [] = {
            // генерируется случайный массив
            {generateRandomArray, "random"},
            // генерируется массив 0, 1, 2, ..., n - 1
            {generateOrderedArray, "ordered"},
            // генерируется массив n - 1, n - 2, ..., 0
            {generateOrderedBackwards, "orderedBackwards"}
    };
    const unsigned CASES_N = ARRAY_SIZE(generatingFuncs);

    // запись статистики в файл
    for (size_t size = 200000; size <= 2000000; size += 200000) {
        printf (" - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        printf (" Size : %d\n", size);
        for (int i = 0; i < FUNCS_N ; i++) {
            for (int j = 0; j < CASES_N ; j++) {
                // генерация имени файла
                char filename[128];
                sprintf(filename, "%s_%s_time", sorts[i].name, generatingFuncs[j].name);
                checkTime(sorts[i].sort, generatingFuncs[j].generate, size, filename);
            }
        }
        printf ("\n") ;
    }
}

void checkNComps(long long (*sortFunc)(int *, size_t), void (*generateFunc)(int *, size_t), size_t size, char *experimentName) {
    static size_t runCounter = 1;

    // генерация последовательности
    static int innerBuffer[100000];
    generateFunc(innerBuffer, size);
    printf("Run #%zu| ", runCounter++);
    printf("Name: %s\n", experimentName);

    long long nComps = sortFunc(innerBuffer, size);

    // результаты замера
    printf (" Status : ") ;
    if (isOrdered(innerBuffer, size)) {
        printf ("OK! Count of comparisons: %lld.\n", nComps);

        // запись в файл
        char filename [256];
        sprintf(filename, "./data/%s.csv", experimentName);
        FILE *f = fopen(filename, "a");
        if (f == NULL) {
            printf (" FileOpenError %s", filename);
            exit(1);
        }
        fprintf(f, "%zu; %lld\n", size, nComps);
        fclose(f);
    } else {
        printf(" Wrong !\n");

        // вывод массива, который не смог быть отсортирован
        outputArray_(innerBuffer, size);

        exit(1);
    }
}

void comparisonsExperiment() {
    // описание функций сортировки
    SortFuncNComps sorts [] = {
            {getExchangeSortNComp, "exchangeSort"},
            {getSelectionSortNComp, "selectionSort"},
            {getInsertionSortNComp, "insertionSort"},
            {getCombSortNComp, "combSort"},
            {getShellSortNComp, "shellSort"},
            {getDigitalSortNComp, "digitalSort"}
            //{ selectionSort , " selectionSort "} ,
            //{ insertionSort , " insertionSort "} ,
            // вы добавите свои сортировки
    };
    const unsigned FUNCS_N = ARRAY_SIZE(sorts);

    // описание функций генерации
    GeneratingFunc generatingFuncs [] = {
            // генерируется случайный массив
            {generateRandomArray, "random"},
            // генерируется массив 0, 1, 2, ..., n - 1
            {generateOrderedArray, "ordered"},
            // генерируется массив n - 1, n - 2, ..., 0
            {generateOrderedBackwards, "orderedBackwards"}
    };
    const unsigned CASES_N = ARRAY_SIZE(generatingFuncs);

    // запись статистики в файл
    for (size_t size = 10000; size <= 100000; size += 10000) {
        printf (" - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        printf (" Size : %d\n", size);
        for (int i = 0; i < FUNCS_N ; i++) {
            for (int j = 0; j < CASES_N; j++) {
                // генерация имени файла
                char filename[128];
                sprintf(filename, "%s_%s_nComps", sorts[i].name, generatingFuncs[j].name);
                checkNComps(sorts[i].sort, generatingFuncs[j].generate, size, filename);
            }
        }
        printf ("\n") ;
    }
}

void measurementForTaskNumber2() {
    SortFunc sorts [] = {
            {shellSort,     "shellSort"}
    };

    GeneratingFunc generatingFuncs [] = {
            {generateRandomArray, "random"},
            {generateOrderedArray, "ordered"},
            {generateOrderedBackwards, "orderedBackwards"}
    };
    const unsigned CASES_N = ARRAY_SIZE(generatingFuncs);

    int size = 1000000;
    printf (" - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    printf (" Size : %d\n", size);

    for (int j = 0; j < CASES_N; j++) {
        // генерация имени файла
        char filename[128];
        sprintf(filename, "%s_%s_time_measurement", sorts[0].name, generatingFuncs[j].name);
        checkTime(sorts[0].sort, generatingFuncs[j].generate, size, filename);
    }
}

int main() {
    //timeExperimentSlowSorting();
    timeExperimentQuickSorting();
    //comparisonsExperiment();

    //measurementForTaskNumber2();
    return 0;
}
