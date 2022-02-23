#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#ifndef UNTITLED10_MATRIX_H
#define UNTITLED10_MATRIX_H


typedef struct {
    int **values;
    int nRows;
    int nCols;
} matrix;

typedef struct {
    float **values;
    int nRows;
    int nCols;
} matrixF;

typedef struct position {
    int rowIndex;
    int colIndex;
} position;

//размещает в динамической памяти матрицу размером nRows на nCols. Возвращает матрицу
matrix getMemMatrix(int nRows, int nCols);

//размещает в динамической памяти массив из nMatrices матриц размером nRows на nCols.
// Возвращает указатель на нулевую матрицу.
matrix *getMemArrayOfMatrices(int nMatrices,
                              int nRows, int nCols);

//освобождает память, выделенную под хранение матрицы m.
void freeMemMatrix(matrix m);

//освобождает память, выделенную под хранение массива ms из nMatrices матриц
void freeMemMatrices(matrix *ms, int nMatrices);

//ввод матрицы m.
void inputMatrix(matrix m);

//ввод массива из nMatrices матриц, хранящейся по адресу ms.
void inputMatrices(matrix *ms, int nMatrices);

//вывод матрицы m
void outputMatrix(matrix m);

void outputMatrixF(matrixF m);

//вывод массива из nMatrices матриц, хранящейся по адресу ms
void outputMatrices(matrix *ms, int nMatrices);

//обмен строк с порядковыми номерами i1 и i2 в матрице m.
void swapRows(matrix m, int i1, int i2);

//обмен колонок с порядковыми номерами j1 и j2 в матрице m.
void swapColumns(matrix m, int j1, int j2);

//выполняет сортировку вставками строк
//матрицы m по неубыванию значения функции criteria применяемой для
//строк
void insertionSortRowsMatrixByRowCriteria(matrix m, int (criteria)(int *, int));

//выполняет сортировку вставками
//столбцов матрицы m по неубыванию значения функции criteria применяемой для столбцов
void insertionSortColsMatrixByColCriteria(matrix m, int (criteria)(int *, int));

//возвращает значение ’истина’, если
//матрица m является квадратной, ложь – в противном случае
bool isSquareMatrix(matrix m);

//возвращает значение
//’истина’, если матрицы m1 и m2 равны, ложь – в противном случае
bool twoMatricesEqual(matrix m1, matrix m2);

//возвращает значение ’истина’, если матрица
//m является единичной, ложь – в противном случае
bool isEMatrix(matrix m);

//возвращает значение ’истина’, если
//матрица m является симметричной, ложь – в противном случае
bool isSymmetricMatrix(matrix m);

//транспонирует квадратную матрицу m.
void transposeSquareMatrix(matrix m);

//возвращает позицию минимального элемента матрицы m.
position getMinValuePos(matrix m);

//возвращает позицию максимального элемента матрицы m.
position getMaxValuePos(matrix m);

//возвращает матрицу, размера nRows на nCols, построенного из элементов массива a,
// размещенную в динамической памяти
matrix createMatrixFromArray(const int *a, size_t nRows,
                             size_t nCols);

//возвращает указатель на нулевую матрицу массива из nMatrices матриц, размещенных
//в динамической памяти, построенных из элементов массива a
matrix *createArrayOfMatrixFromArray(const int *values,
                                     size_t nMatrices, size_t nRows, size_t nCols);

long long getSum(int *a, int n);


#endif //UNTITLED10_MATRIX_H
