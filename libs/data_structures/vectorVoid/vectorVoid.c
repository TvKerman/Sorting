//
// Created by Григорий on 02.02.2022.
//

#include "vectorVoid.h"
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>

static size_t min(size_t a, size_t b) {
    return a < b ? a : b;
}

vectorVoid createVectorV(size_t n, size_t baseTypeSize) {
    vectorVoid v;

    v.data = malloc(n * baseTypeSize);
    v.size = 0;
    v.capacity = n;
    v.baseTypeSize = baseTypeSize;

    if (v.data == NULL) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }

    return v;
}

void reserveV(vectorVoid *v, size_t newCapacity) {
    v->data = realloc(v->data, newCapacity * v->baseTypeSize);
    v->size = min(v->size, newCapacity);
    v->capacity = newCapacity;

    if (v->data == NULL && v->capacity != 0) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
}

void shrinkToFitV(vectorVoid *v) {
    reserveV(v, v->size);
}

void clearV(vectorVoid *v) {
    v->size = 0;
}

void deleteVectorV(vectorVoid *v) {
    free(v->data);
    v->size = 0;
    v->capacity = 0;
    v->baseTypeSize = 0;
}

bool isEmptyV(vectorVoid *v) {
    return v->size == 0;
}

bool isFullV(vectorVoid *v) {
    return v->size == v->capacity;
}

void getVectorValueV(vectorVoid *v, size_t index, void *destination) {
    if (v->size <= index) {
        fprintf(stderr, "IndexError: a[%llu] is not exists", index);
        exit(1);
    }

    char *source = (char *) v->data + index * v->baseTypeSize;
    memcpy(destination, source, v->baseTypeSize);
}

void setVectorValueV(vectorVoid *v, size_t index, void *source) {
    if (v->size <= index) {
        fprintf(stderr, "IndexError: a[%llu] is not exists", index);
        exit(1);
    }

    char *destination = (char *) v->data + index * v->baseTypeSize;
    memcpy(destination, source, v->baseTypeSize);
}

void popBackV(vectorVoid *v) {
    if (isEmptyV(v)) {
        fprintf(stderr, "void vector");
        exit(1);
    }

    v->size--;
}

void pushBackV(vectorVoid *v, void *source){
    if (v->capacity == 0) {
        reserveV(v, 1);
    } else if (isFullV(v)) {
        reserveV(v, v->capacity * 2);
    }

    setVectorValueV(v, v->size++, source);
}