//
// Created by Григорий on 02.02.2022.
//

#ifndef INC_VECTORVOID_H
#define INC_VECTORVOID_H

#include <limits.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct vectorVoid {
    void *data;             // указатель на нулевой элемент вектора
    size_t size;            // размер вектора
    size_t capacity;        // вместимость вектора
    size_t baseTypeSize;    // размер базового типа:
                            // например, если вектор хранит int -
                            // то поле baseTypeSize = sizeof(int)
                            // если вектор хранит float -
                            // то поле baseTypeSize = sizeof(float)
} vectorVoid;

// Возвращает структуру-дескриптор vectorVoid, имеющую n элементов размера типа baseTypeSize.
vectorVoid createVectorV(size_t n, size_t baseTypeSize);

// Изменяет количество памяти, выделенное под хранение элементов вектора v.
// Количество выделенных ячеек памяти становится равным newCapacity.
void reserveV(vectorVoid *v, size_t newCapacity);

// Освобождает память, выделенную под неиспользуемые элементы вектора v.
void shrinkToFitV(vectorVoid *v);

// Удаляет все элементы из вектора v. Не освобождает выделенную память.
void clearV(vectorVoid *v);

// Освобождает память, выделенную под элементы вектора v.
void deleteVectorV(vectorVoid *v);

//Возвращает true, если вектор v не содержит элементов.
//Иначе - false.
bool isEmptyV(vectorVoid *v);

// Возвращает true, если вектор v полностью заполнен.
// Иначе - false.
bool isFullV(vectorVoid *v);

// Записывает по адресу destination index-ый элемент вектора v.
void getVectorValueV(vectorVoid *v, size_t index, void *destination);

// Записывает на index-ый элемент вектора v значение, расположенное по
// адресу source;
void setVectorValueV(vectorVoid *v, size_t index, void *source);

// Удаляет последний элемент вектора v. Если вектор пуст,
// выводит сообщение об ошибке и прекращает работу.
void popBackV(vectorVoid *v);

// Добавляет элемент x в конец вектора v. Если вектор заполнен,
// увеличивает количество выделенной памяти в 2 раза и добавляет элемент.
void pushBackV(vectorVoid *v, void *source);

#endif //INC_VECTORVOID_H
