//
// Created by Григорий on 11.02.2022.
//

#include "matrix.h"

static void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **)malloc(sizeof(int *) * nRows);
    for (int i = 0; i < nRows; i++) {
        values[i] = (int *)malloc(sizeof(int *) * nCols);
    }
    return (matrix){values, nRows, nCols};
}

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols) {
    matrix *ms = (matrix *)malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++) {
        ms[i] = getMemMatrix(nRows, nCols);
    }
    return ms;
}

void freeMemMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        free(m.values[i]);
    }
    free(m.values);
}

void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        freeMemMatrix(ms[i]);
    }
    free(ms);
}

void inputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            scanf("%d", &m.values[i][j]);
        }
    }
}

void inputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        inputMatrix(ms[i]);
    }
}

void outputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        printf("|");
        for (int j = 0; j < m.nCols; j++) {
            printf("%3.1d, ", m.values[i][j]);
        }
        printf("\b\b|\n");
    }
}

void outputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        outputMatrix(ms[i]);
        printf("\n");
    }
}

void swapRows(matrix m, int i1, int i2) {
    if (i1 >= m.nRows || i2 >= m.nRows) {
        fprintf(stderr, "matrix index out of range");
        exit(1);
    }

    int *t = m.values[i1];
    m.values[i1] = m.values[i2];
    m.values[i2] = t;
}

void swapColumns(matrix m, int j1, int j2) {
    if (j1 >= m.nCols || j2 >= m.nCols) {
        fprintf(stderr, "matrix index out of range");
        exit(1);
    }

    for (int i = 0; i < m.nRows; i++) {
        int t = m.values[i][j1];
        m.values[i][j1] = m.values[i][j2];
        m.values[i][j2] = t;
    }
}

void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int *, int)) {
    int *b = (int *)malloc(m.nRows * sizeof(int));

    for (int i = 0; i < m.nRows; i++) {
        b[i] = criteria(m.values[i], m.nCols);
    }

    for (int i = 0; i < m.nRows - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < m.nRows; j++) {
            if (b[j] < b[minIndex]) {
                minIndex = j;
            }
        }
        swapRows(m, minIndex, i);
        swap(&b[minIndex], &b[i]);
    }

    free(b);
}

void insertionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int *, int)) {
    int *a = (int *)malloc(m.nRows * sizeof(int));
    int *b = (int *)malloc(m.nCols * sizeof(int));

    for (int i = 0; i < m.nCols; i++) {
        for (int j = 0; j < m.nRows; j++) {
            a[j] = m.values[j][i];
        }
        b[i] = criteria(a, m.nRows);
    }

    for (int i = 0; i < m.nCols - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < m.nCols; j++) {
            if (b[j] < b[minIndex]) {
                minIndex = j;
            }
        }
        swapColumns(m, minIndex, i);
        swap(&b[minIndex], &b[i]);
    }

    free(a);
    free(b);
}

bool isSquareMatrix(matrix m) {
    return m.nRows == m.nCols;
}

bool twoMatricesEqual(matrix m1, matrix m2) {
    if (m1.nRows != m2.nRows || m1.nCols != m2.nCols) {
        return false;
    }

    for (int i = 0; i < m1.nRows; i++) {
        for (int j = 0; j < m1.nCols; j++) {
            if (m1.values[i][j] != m2.values[i][j]) {
                return false;
            }
        }
    }

    return true;
}

bool isEMatrix(matrix m) {
    if (!isSquareMatrix(m)) {
        return false;
    }

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (i == j && m.values[i][j] != 1) {
                return false;
            } else if (i != j && m.values[i][j] != 0) {
                return false;
            }
        }
    }

    return true;
}

bool isSymmetricMatrix(matrix m) {
    if (!isSquareMatrix(m)) {
        return false;
    }

    for (int i = 0; i < m.nRows; i++) {
        for (int j = i + 1; j < m.nCols; j++) {
            if (m.values[i][j] != m.values[j][i]) {
                return false;
            }
        }
    }

    return true;
}

void transposeSquareMatrix(matrix m) {
    if (!isSquareMatrix(m)) {
        fprintf(stderr, "is not square matrix");
        exit(1);
    }

    for (int i = 0; i < m.nRows; i++) {
        for (int j = i + 1; j < m.nCols; j++) {
            swap(&m.values[i][j], &m.values[j][i]);
        }
    }
}

position getMinValuePos(matrix m) {
    position minPos = {0, 0};

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[minPos.rowIndex][minPos.colIndex] > m.values[i][j]) {
                minPos.rowIndex = i;
                minPos.colIndex = j;
            }
        }
    }

    return minPos;
}

position getMaxValuePos(matrix m) {
    position maxPos = {0, 0};

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[maxPos.rowIndex][maxPos.colIndex] < m.values[i][j]) {
                maxPos.rowIndex = i;
                maxPos.colIndex = j;
            }
        }
    }

    return maxPos;
}

matrix createMatrixFromArray(const int *a, size_t nRows, size_t nCols) {
    matrix m = getMemMatrix(nRows, nCols);

    int k = 0;
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            m.values[i][j] = a[k++];
        }
    }

    return m;
}

matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices, size_t nRows, size_t nCols) {
    matrix * ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);

    int l = 0;
    for (int k = 0; k < nMatrices; k++) {
        for (int i = 0; i < nRows; i++) {
            for (int j = 0; j < nCols; j++) {
                ms[k].values[i][j] = values[l++];
            }
        }
    }

    return ms;
}

matrixD getMemMatrixD(int nRows, int nCols) {
    double **values = (double **)malloc(sizeof(double *) * nRows);
    for (int i = 0; i < nRows; i++) {
        values[i] = (double *)malloc(sizeof(double *) * nCols);
    }
    return (matrixD){values, nRows, nCols};
}

matrixD *getMemArrayOfMatricesD(int nMatrices, int nRows, int nCols) {
    matrixD *ms = (matrixD *)malloc(sizeof(matrixD) * nMatrices);
    for (int i = 0; i < nMatrices; i++) {
        ms[i] = getMemMatrixD(nRows, nCols);
    }
    return ms;
}

void freeMemMatrixD(matrixD m) {
    for (int i = 0; i < m.nRows; i++) {
        free(m.values[i]);
    }
    free(m.values);
}

void freeMemMatricesD(matrixD *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        freeMemMatrixD(ms[i]);
    }
    free(ms);
}

void inputMatrixD(matrixD m) {
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            scanf("%lf", &m.values[i][j]);
        }
    }
}

void inputMatricesD(matrixD *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        inputMatrixD(ms[i]);
    }
}

void outputMatrixD(matrixD m) {
    for (int i = 0; i < m.nRows; i++) {
        printf("|");
        for (int j = 0; j < m.nCols; j++) {
            printf("%3.1lf, ", m.values[i][j]);
        }
        printf("\b\b|\n");
    }
}