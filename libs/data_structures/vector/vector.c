#include <stdio.h>
#include "vector.h"
#include <stdint.h>
#include <malloc.h>
#include <stdbool.h>


vector createVector(size_t n) {
    int *v = malloc(sizeof(int) * n);
    if (v == NULL) {
        fprintf(stderr, " bad alloc ");
        exit(1);
    }
    else if (n == 0){
        v = NULL;
    }
    return (vector) {v, 0, n};
}

void reserve(vector *v, size_t newCapacity) {
    if (newCapacity == 0) {
        v->data = NULL;
    }
    else if (newCapacity < v->size) {
        v->size = newCapacity;
    }
    else if (v->data == NULL){
        fprintf(stderr, "bad alloc");
        exit(1);
    }

    v->data = realloc(v->data, sizeof(int) * newCapacity);
    v->capacity = newCapacity;
}

void clear(vector *v) {
    v->size = 0;
}

void shrinkToFit(vector *v) {
    reserve(v, v->size);
}

void deleteVector(vector *v) {
    reserve(v, 0);
}

bool isEmpty(vector *v) {
    return v->size == 0;
}

bool isFull(vector *v) {
    return v->size == v->capacity;
}

int getVectorValue(vector *v, size_t i) {
    return v->data;
}

void pushBack(vector *v, int x){
    if(v->capacity == 0) {
        reserve(v, 1);
    }
    else if(isFull(v)) {
        reserve(v, v->capacity * 2);
    }

    v->data[v->size] = x;
    v->size++;
}

void popBack(vector *v){
    if(isEmpty(v)){
        fprintf(stderr, " bad alloc ");
        exit(1);
    }

    v->size--;
}
int* atVector(vector *v, size_t index){
    if(index > v->size) {
        fprintf(stderr, "IndexError: a[%lld] is not exists0", index);
        exit(1);
    }

    return &v->data[index];
}

int* back(vector *v){
    if(isEmpty(v)){
        return NULL;
    }
    return &v->data[v->size - 1];
}

int* front(vector *v){
    if(isEmpty(v)){
        return NULL;
    }

    return atVector(v, 0);
}

