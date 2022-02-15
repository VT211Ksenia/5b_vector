#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#ifndef UNTITLED10_MATRIX_H
#define UNTITLED10_MATRIX_H


typedef struct matrix{
    int **values;
    int nRows;
    int nCols;
} matrix;

typedef struct position{
    int rowIndex;
    int colIndex;
}position;

matrix getMemMatrix(int nRows, int nCols);

matrix * getMemArrayOfMatrices ( int nMatrices ,
                                 int nRows , int nCols );

void freeMemMatrix(matrix m);

void inputMatrix(matrix m);

void inputMatrices(matrix *ms, int nMatrices);

void outputMatrix(matrix m);

void outputMatrices(matrix *ms, int nMatrices);

void swapRows(matrix m, int i1, int i2);

void swapColumns(matrix m, int j1, int j2);

int getMax(const int *a, int n);

void insertionSortRowsMatrixByRowCriteria(matrix m, int (criteria)(int *, int));

void insertionSortColsMatrixByColCriteria(matrix m, int (criteria)(int *, int));

int getMin(const int *a, int n);


#endif //UNTITLED10_MATRIX_H
