#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <stdbool.h>
#include "matrix.h"

void badIndex() {
    fprintf(stderr, "bad index\n");
    exit(1);
}

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int *) * nRows);
    for (int i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof(int) * nCols);
    return (matrix) {values, nRows, nCols};

}

matrix *getMemArrayOfMatrices(int nMatrices,
                              int nRows, int nCols) {
    matrix *ms = (matrix *) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);
    return ms;
}

void freeMemMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++)
        free(m.values[i]);
    free(m.values);
}

void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++)
        freeMemMatrix(ms[i]);
    free(ms->values);
}

void inputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++)
        for (int j = 0; j < m.nCols; j++)
            scanf("%d", &m.values[i][j]);
}

void inputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++)
        inputMatrix(ms[i]);
}

void outputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++)
            printf("%d ", m.values[i][j]);
        printf("\b\b\n");
    }
}

void outputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        outputMatrix(ms[i]);
        printf("\n");
    }
}


void swapRows(matrix m, int i1, int i2) {
    swap((int*)&m.values[i1], (int*)&m.values[i2]);
}

void swapColumns(matrix m, int j1, int j2) {
    for (int i = 0; i < m.nRows; i++)
        swap(&m.values[i][j1], &m.values[i][j2]);
}


void insertionSortRowsMatrixByRowCriteria(matrix m, int (criteria)(int *, int)) {
    int criteriaArray[m.nRows];
    for (size_t i = 0; i < m.nRows; ++i)
        criteriaArray[i] = criteria(m.values[i], m.nCols);

    for (int i = 1; i < m.nRows; ++i) {
        int j = i;
        while (j > 0 && criteriaArray[j - 1] > criteriaArray[j]) {
            swap(&criteriaArray[j - 1], &criteriaArray[j]);
            swapRows(m, j - 1, j);

            j--;
        }
    }
}

void insertionSortColsMatrixByColCriteria(matrix m, int (criteria)(int *, int)) {
    int criteriaArray[m.nCols];
    for (size_t i = 0; i < m.nCols; ++i) {
        int arrayForRow[m.nRows];
        for (size_t j = 0; j < m.nRows; ++j)
            arrayForRow[j] = m.values[i][j];

        criteriaArray[i] = criteria(arrayForRow, m.nRows);
    }

    for (int i = 1; i < m.nCols; ++i) {
        int j = i;
        while (j > 0 && criteriaArray[j - 1] > criteriaArray[j]) {
            swap(&criteriaArray[j - 1], &criteriaArray[j]);
            swapColumns(m, j - 1, j);

            j--;
        }
    }
}

bool isSquareMatrix(matrix m) {
    if (m.nRows == m.nCols)
        return true;
    else
        return false;
}

bool twoMatricesEqual(matrix m1, matrix m2){
    if(m1.nRows != m2.nRows || m1.nCols != m2.nCols)
        return false;
    for( int i = 0; i < m1.nRows; i++)
        for( int j = 0; j < m1.nCols; j++)
            if(m1.values[i][j] != m2.values[i][j])
                return false;

    return true;
}

bool isEMatrix(matrix m){
    if(!isSquareMatrix(m))
        return false;
    for(int i = 0; i < m.nRows; i++)
        for(int j = 0; j < m.nCols; i++)
            if ((i != j && m.values[i][j]!= 0) || (i == j && m.values[i][j] != 1))
                return false;
    return true;
}

bool isSymmetricMatrix(matrix m) {
    if(!isSquareMatrix(m))
        return false;
    for(int i = 0; i < m.nRows; i++)
        for(int j = 0; j < m.nCols; i++)
            if(m.values[i][j] != m.values[j][i])
                return false;
    return true;

}
void transposeSquareMatrix(matrix m){
    if(isSquareMatrix(m)) {
        for (int i = 0; i < m.nRows; i++)
            for (int j = 0; j < m.nCols; i++)
                if (i == j)
                    swap((int *) &m.values[i][j], (int *) &m.values[j][i]);
    }
}
position getMinValuePos(matrix m){
    int minValue = m.values[0][0];
    position minPos = {0, 0};

    for (int i = 0; i < m.nRows; i++)
        for (int j = 1; j < m.nCols; i++)
            if(m.values[i][j] < minValue) {
                minValue = m.values[i][j];
                minPos.colIndex = j;
                minPos.rowIndex = i;
            }
    return minPos;

}

position getMaxValuePos(matrix m){
    int maxValue = m.values[0][0];
    position maxPos = {0, 0};

    for (int i = 0; i < m.nRows; i++)
        for (int j = 1; j < m.nCols; i++)
            if(m.values[i][j] > maxValue) {
                maxValue = m.values[i][j];
                maxPos.colIndex = j;
                maxPos.rowIndex = i;
            }
    return maxPos;
}
matrix createMatrixFromArray(const int *a, size_t nRows,
                             size_t nCols){
    matrix m = getMemMatrix(nRows, nCols);

    int k = 0;
    for(int i = 0; i < nRows; i++)
        for( int j = 0; j < nCols; j++)
            m.values[i][j] = a[k++];

    return m;
}
matrix *createArrayOfMatrixFromArray(const int *values,
                                     size_t nMatrices, size_t nRows, size_t nCols){
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);
    int  l = 0;
    for(int k = 0; k < nMatrices; k++)
        for(int i = 0; i < nRows; i++)
            for(int j = 0; j < nCols; j++)
                ms[k].values[i][j] = values[l++];
    return ms;
}
// первая задача
void swapRowsWithMaxAndMinValue(matrix m) {
    position minIndex = getMinValuePos(m);
    position maxIndex = getMaxValuePos(m);
    if (minIndex.rowIndex != maxIndex.rowIndex)
        swapRows(m, minIndex.rowIndex, maxIndex.rowIndex);
}

// вторая задача
int getMax(const int *a, int n){
    int maxValue = a[0];
    for(int i = 1; i < n; i++)
        if( a[i] > maxValue)
            maxValue = a[i];
    return maxValue;
}

void secondTask(matrix m){
    insertionSortRowsMatrixByRowCriteria(m, getMax);
}
//третья задача

int getMin(const int *a, int n){
    int minValue = a[0];
    for(int i = 1; i < n; i++)
        if( a[i] < minValue)
            minValue = a[i];
    return minValue;
}

void thirdTask(matrix m){
    insertionSortColsMatrixByColCriteria(m, getMin);
}
// четвертая задача
matrix mulMatrices(matrix m1, matrix m2) {
    if (m1.nCols != m2.nRows) {
        fprintf(stderr, "matrices cannot be multiplied");
        exit(1);
    }

    matrix multiplicationMatrix = getMemMatrix(m1.nRows, m2.nCols);

    for (int indexRowM1 = 0; indexRowM1 < m1.nRows; indexRowM1++)
        for (int indexColM2 = 0; indexColM2 < m2.nCols; indexColM2++) {
            multiplicationMatrix.values[indexRowM1][indexColM2] = 0;
            for (int indexRowM2 = 0; indexRowM2 < m2.nRows; indexRowM2++)
                multiplicationMatrix.values[indexRowM1][indexColM2] +=
                        m1.values[indexRowM1][indexRowM2]
                        * m2.values[indexRowM2][indexColM2];
        }

    return (matrix) multiplicationMatrix;
}
void getSquareOfMatrixIfSymmetric(matrix *m){
    if(isSquareMatrix(*m))
        *m = mulMatrices(*m, *m);
}
// пятая задача
bool isUnique(long long *a, int n){
    for(int i = 0; i < n; i++)
        for (int j = 1; j < n - 1; j++) {
            if(a[i] == a[j])
                return false;


        }
    return true;
}
long long getSum(int *a, int n){
    long long sum = 0;
    for(int i = 0; i < n; i++)
        sum += a[i];
    return sum;
}

void transposeIfMatrixHasEqualSumOfRows(matrix m){
    int a[m.nRows];
    for(int i = 0; i< m.nRows; i++)
        a[i] = getSum(m.values[i], m.nCols);

    if(isUnique(a, m.nRows ))
        transposeSquareMatrix(m);

}
// шестая задача
bool isMutuallyInverseMatrices(matrix m1, matrix m2){
    matrix m3 = mulMatrices(m1, m2);
    if(!isEMatrix(m3))
        return false;
    return true;
}