//
// Created by Григорий on 11.02.2022.
//

#ifndef MATRICES_MATRIX_H
#define MATRICES_MATRIX_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct matrix {
    int **values;       // Элементы матрицы
    int nRows;          // Количество рядов
    int nCols;          // Количество столбцов
} matrix;

typedef struct matrixD {
    double **values;       // Элементы матрицы
    int nRows;          // Количество рядов
    int nCols;          // Количество столбцов
} matrixD;

typedef struct position {
    int rowIndex;
    int colIndex;
} position;

matrix getMemMatrix(int nRows, int nCols);

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols);

void freeMemMatrix(matrix m);

void freeMemMatrices(matrix *ms, int nMatrices);

void inputMatrix(matrix m);

void inputMatrices(matrix *ms, int nMatrices);

void outputMatrix(matrix m);

void outputMatrices(matrix *ms, int nMatrices);

void swapRows(matrix m, int i1, int i2);

void swapColumns(matrix m, int j1, int j2);

void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int *, int));

void insertionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int *, int));

bool isSquareMatrix(matrix m);

bool twoMatricesEqual(matrix m1, matrix m2);

bool isEMatrix(matrix m);

bool isSymmetricMatrix(matrix m);

void transposeSquareMatrix(matrix m);

position getMinValuePos(matrix m);

position getMaxValuePos(matrix m);

matrix createMatrixFromArray(const int *a, size_t nRows, size_t nCols);

matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices, size_t nRows, size_t nCols);

matrixD getMemMatrixD(int nRows, int nCols);

matrixD *getMemArrayOfMatricesD(int nMatrices, int nRows, int nCols);

void freeMemMatrixD(matrixD m);

void freeMemMatricesD(matrixD *ms, int nMatrices);

void inputMatrixD(matrixD m);

void inputMatricesD(matrixD *ms, int nMatrices);

void outputMatrixD(matrixD m);

#endif //MATRICES_MATRIX_H
