//
// Created by Григорий on 01.02.2022.
//
#ifndef INC_VECTOR_H
#define INC_VECTOR_H

#include <stdio.h>
#include <stdbool.h>

typedef struct vector {
    int *data;          // указатель на элементы вектора
    size_t size;        // размер вектора
    size_t capacity;    // вместимость вектора
} vector;

// Возвращает структуру-дескриптор vector из n значений.
vector createVector(size_t n);

// Изменяет количество памяти, выделенное под хранение элементов вектора v.
// Количество выделенных ячеек памяти становится равным newCapacity.
void reserve(vector *v, size_t newCapacity);

// Удаляет все элементы из вектора v. Не освобождает выделенную память.
void clear(vector *v);

// Освобождает память, выделенную под неиспользуемые элементы вектора v.
void shrinkToFit(vector *v);

// Освобождает память, выделенную под элементы вектора v.
void deleteVector(vector *v);

//Возвращает true, если вектор v не содержит элементов.
//Иначе - false.
bool isEmpty(vector *v);

// Возвращает true, если вектор v полностью заполнен.
// Иначе - false.
bool isFull(vector *v);

// Возвращает i-ый элемент вектора v.
int getVectorValue(vector *v, size_t i);

// Добавляет элемент x в конец вектора v. Если вектор заполнен,
// увеличивает количество выделенной памяти в 2 раза и добавляет элемент.
void pushBack(vector *v, int x);

// Удаляет последний элемент вектора v. Если вектор пуст,
// выводит сообщение об ошибке и прекращает работу.
void popBack(vector *v);

// Возвращает указатель на index-ый элемент вектора v.
// Если осуществляется попытка получить доступ вне пределов
// используемых элементов вектора, выводит сообщение об ошибке
// и прекращает работу.
int* atVector(vector *v, size_t index);

// Возвращает указатель на последний элемент вектора v.
int* back(vector *v);

// Возвращает указатель на первый элемент вектора v.
int* front(vector *v);

#endif //INC_VECTOR_H
