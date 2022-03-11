//
// Created by Григорий on 01.02.2022.
//

#include "vector.h"
#include <malloc.h>
#include <stdlib.h>

static size_t min(size_t a, size_t b) {
    return a < b ? a : b;
}

vector createVector(size_t n) {
    vector v;

    v.data = (int *)malloc(n * sizeof(int));
    v.size = 0;
    v.capacity = n;

    if (v.data == NULL) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }

    return v;
}

void reserve(vector *v, size_t newCapacity) {
    v->data = (int *)realloc(v->data, newCapacity * sizeof(int));
    v->size = min(v->size, newCapacity);
    v->capacity = newCapacity;

    if (v->data == NULL && v->capacity != 0) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
}

void clear(vector *v) {
    v->size = 0;
}

void shrinkToFit(vector *v) {
    reserve(v, v->size);
}

void deleteVector(vector *v) {
    free(v->data);
    v->size = 0;
    v->capacity = 0;
}

bool isEmpty(vector *v) {
    return v->size == 0;
}

bool isFull(vector *v) {
    return v->size == v->capacity;
}

int getVectorValue(vector *v, size_t i) {
    return v->data[i];
}

void pushBack(vector *v, int x) {
    if (v->capacity == 0) {
        reserve(v, 1);
    } else if (isFull(v)) {
        reserve(v, v->capacity * 2);
    }
    v->data[v->size++] = x;
}

void popBack(vector *v) {
    if (isEmpty(v)) {
        fprintf(stderr, "void vector");
        exit(1);
    }
    v->size--;
}

int* atVector(vector *v, size_t index) {
    if (v->size <= index) {
        fprintf(stderr, "IndexError: a[%llu] is not exists", index);
        exit(1);
    }
    return v->data + index;
}

int* back(vector *v) {
    return atVector(v, v->size - 1);
}

int* front(vector *v) {
    return atVector(v, 0);
}