#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include "C:\Users\User\CLionProjects\untitled10\libs/algorithms/array/array.h"

#ifndef UNTITLED10_VECTOR_H
#define UNTITLED10_VECTOR_H

typedef struct vector{
    int *data; // указатель на элемент вектора
    size_t size; // размер вектора
    size_t capacity;// вместимость вектора
} vector;


// возвращает структуру-дескриптор вектора из n значений
vector createVector(size_t n);

//изменяет количество памяти, выделенное под хранение элемента вектора
void reserve(vector *v, size_t ntwCapfcity);

//удаляет элементы из контейнера, не освобождая память
void clear(vector *v);

//освобождает память, выденную под неиспользуемые элементы
void shrinkToFit(vector *v);

//освобождает память, выделенную вектору
void deleteVector(vector *v)


#endif
