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
    return (vector) {v, 0, n};
}

void reserve(vector *v, size_t newCapacity) {
    if (newCapacity == 0)
        v->data = NULL;
    else if (newCapacity < v->size)
        v->size = newCapacity;
    else {
        v->data = realloc(v->data, sizeof(int) * newCapacity);
        if (v == NULL) {
            fprintf(stderr, " bad alloc ");
            exit(1);
        }
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
}

