#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <stdbool.h>
#include "matrix.h"
#include <memory.h>

void badIndex() {
    fprintf(stderr, "bad index\n");
    exit(1);
}

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

//размещает в динамической памяти матрицу размером nRows на nCols. Возвращает матрицу
matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int *) * nRows);
    for (int i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof(int) * nCols);
    return (matrix) {values, nRows, nCols};

}

//размещает в динамической памяти массив из nMatrices матриц размером nRows на nCols.
// Возвращает указатель на нулевую матрицу.
matrix *getMemArrayOfMatrices(int nMatrices,
                              int nRows, int nCols) {
    matrix *ms = (matrix *) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);
    return ms;
}

//освобождает память, выделенную под хранение матрицы m.
void freeMemMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++)
        free(m.values[i]);
    free(m.values);
}

//освобождает память, выделенную под хранение массива ms из nMatrices матриц
void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++)
        freeMemMatrix(ms[i]);
    free(ms->values);
}

//ввод матрицы m.
void inputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++)
        for (int j = 0; j < m.nCols; j++)
            scanf("%d", &m.values[i][j]);
}

//ввод массива из nMatrices матриц, хранящейся по адресу ms.
void inputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++)
        inputMatrix(ms[i]);
}

//вывод матрицы m
void outputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++)
            printf("%d ", m.values[i][j]);
        printf("\b\b\n");
    }
}

//вывод массива из nMatrices матриц, хранящейся по адресу ms
void outputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        outputMatrix(ms[i]);
        printf("\n");
    }
}

//обмен строк с порядковыми номерами i1 и i2 в матрице m.
void swapRows(matrix m, int i1, int i2) {
    swap((int *) &m.values[i1], (int *) &m.values[i2]);
}

//обмен колонок с порядковыми номерами j1 и j2 в матрице m.
void swapColumns(matrix m, int j1, int j2) {
    for (int i = 0; i < m.nRows; i++)
        swap(&m.values[i][j1], &m.values[i][j2]);
}

//выполняет сортировку вставками строк
//матрицы m по неубыванию значения функции criteria применяемой для
//строк
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

//выполняет сортировку вставками
//столбцов матрицы m по неубыванию значения функции criteria применяемой для столбцов
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

//возвращает значение ’истина’, если
//матрица m является квадратной, ложь – в противном случае
bool isSquareMatrix(matrix m) {
    return m.nRows == m.nCols;
}




//возвращает значение
//’истина’, если матрицы m1 и m2 равны, ложь – в противном случае
bool twoMatricesEqual(matrix m1, matrix m2) {
    if (m1.nRows != m2.nRows || m1.nCols != m2.nCols)
        return false;
    for (int i = 0; i < m1.nRows; i++)
        //for (int j = 0; j < m1.nCols; j++)
            if(memcmp(m1.values[i], m2.values[i], sizeof (int) * m1.nCols))
            //if (m1.values[i][j] != m2.values[i][j])
                return false;

    return true;
}

//возвращает значение ’истина’, если матрица
//m является единичной, ложь – в противном случае
bool isEMatrix(matrix m) {
    if (!isSquareMatrix(m))
        return false;
    for (int i = 0; i < m.nRows; i++)
        for (int j = 0; j < m.nCols; i++)
            if ((i != j && m.values[i][j] != 0) || (i == j && m.values[i][j] != 1));
                return false;
    return true;
}

//возвращает значение ’истина’, если
//матрица m является симметричной, ложь – в противном случае

bool isSymmetricMatrix(matrix m) {
    if (!isSquareMatrix(m))
        return false;
    for (int i = 0; i < m.nRows; i++)
        for (int j = i+1; j < m.nCols; i++)
            if (m.values[i][j] != m.values[j][i])
                return false;
    return true;

}

//транспонирует квадратную матрицу m.
void transposeSquareMatrix(matrix m) {
    if (isSquareMatrix(m)) {
        for (int i = 0; i < m.nRows; i++)
            for (int j = 0; j < m.nCols; i++)
                if (i == j)
                    swap((int *) &m.values[i][j], (int *) &m.values[j][i]);
    }
}

//возвращает позицию минимального элемента матрицы m.
position getMinValuePos(matrix m) {
    int minValue = m.values[0][0];
    position minPos = {0, 0};

    for (int i = 0; i < m.nRows; i++)
        for (int j = 1; j < m.nCols; i++)
            if (m.values[i][j] < minValue) {
                minValue = m.values[i][j];
                minPos.colIndex = j;
                minPos.rowIndex = i;
            }
    return minPos;

}

//возвращает позицию максимального элемента матрицы m.
position getMaxValuePos(matrix m) {
    int maxValue = m.values[0][0];
    position maxPos = {0, 0};

    for (int i = 0; i < m.nRows; i++)
        for (int j = 1; j < m.nCols; i++)
            if (m.values[i][j] > maxValue) {
                maxValue = m.values[i][j];
                maxPos.colIndex = j;
                maxPos.rowIndex = i;
            }
    return maxPos;
}

//возвращает матрицу, размера nRows на nCols, построенного из элементов массива a,
// размещенную в динамической памяти
matrix createMatrixFromArray(const int *a, size_t nRows,
                             size_t nCols) {
    matrix m = getMemMatrix(nRows, nCols);

    int k = 0;
    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            m.values[i][j] = a[k++];

    return m;
}

//возвращает указатель на нулевую матрицу массива из nMatrices матриц, размещенных
//в динамической памяти, построенных из элементов массива a
matrix *createArrayOfMatrixFromArray(const int *values,
                                     size_t nMatrices, size_t nRows, size_t nCols) {
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);
    int l = 0;
    for (int k = 0; k < nMatrices; k++)
        for (int i = 0; i < nRows; i++)
            for (int j = 0; j < nCols; j++)
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
int getMax(const int *a, int n) {
    int maxValue = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] > maxValue)
            maxValue = a[i];
    return maxValue;
}

void secondTask(matrix m) {
    insertionSortRowsMatrixByRowCriteria(m, getMax);
}
//третья задача

int getMin(const int *a, int n) {
    int minValue = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] < minValue)
            minValue = a[i];
    return minValue;
}

void thirdTask(matrix m) {
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

void getSquareOfMatrixIfSymmetric(matrix *m) {
    if (isSquareMatrix(*m))
        *m = mulMatrices(*m, *m);
}
// пятая задача
bool isUnique(long long *a, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 1; j < n - 1; j++) {
            if (a[i] == a[j])
                return false;


        }
    return true;
}

long long getSum(int *a, int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++)
        sum += a[i];
    return sum;
}

void transposeIfMatrixHasEqualSumOfRows(matrix m) {
    int a[m.nRows];
    for (int i = 0; i < m.nRows; i++)
        a[i] = getSum(m.values[i], m.nCols);

    if (isUnique(a, m.nRows))
        transposeSquareMatrix(m);

}
// шестая задача
bool isMutuallyInverseMatrices(matrix m1, matrix m2) {
    matrix m3 = mulMatrices(m1, m2);
    if (!isEMatrix(m3))
        return false;
    return true;
}

// седьмая задача
int max(int a, int b) {
    return a > b ? a : b;
}

int getMaxElementDiagonal(matrix m, int iRow, int iCol) {
    int maxValue = m.values[iRow][iCol];
    while (iRow < m.nRows && iCol < m.nCols)
        maxValue = max(maxValue, m.values[iRow++][iCol++]);
    return maxValue;
}


long long findSumOfMaxesOfPseudoDiagonal(matrix m) {
    int sum = 0;
    for (int i = 1; i < m.nRows; i++)
        sum += getMaxElementDiagonal(m, i, 0);

    for (int j = 1; j < m.nCols; j++) {
        sum += getMaxElementDiagonal(m, 0, j);
    }
    return sum;
}

// восьмая задача

int min(int a, int b) {
    return a > b ? b : a;
}

int getMinInArea(matrix m) {
    position minPos = getMaxValuePos(m);
    int minElem = m.values[minPos.rowIndex][minPos.colIndex];

    int jRight = minPos.colIndex;
    int jLeft = minPos.colIndex;
    for (int i = minPos.rowIndex - 1; i >= 0; i--) {
        jLeft = jLeft > 0 ? jLeft - 1 : jLeft;
        jRight = jRight < m.nCols ? jRight + 1 : jRight;

        minElem = min(getMin(&m.values[i][jLeft], jRight - jLeft), minElem);

    }
    return minElem;
}


void transposeMatrix(matrix m) {
        for (int i = 0; i < m.nRows; i++)
            for (int j = 0; j < m.nCols; i++)
                if (i == j)
                    swap((int *) &m.values[i][j], (int *) &m.values[j][i]);
    }


//     9 задача   //
float getDistance(int *a, int n){
    double sum = 0;
    for( int i = 0; i < n; i++)
        sum += pow(a[i], 2);
    return sqrt(sum);
}

void swapF(float *a, float *b){
    float temp = *b;
    *b = *a;
    *a = temp;
}

void insertionSortRowsMatrixByRowCriteriaF(matrix m, float (criteria)(int *, int)) {
    float criteriaArray[m.nRows];
    for (size_t i = 0; i < m.nRows; ++i)
        criteriaArray[i] = criteria(m.values[i], m.nCols);

    for (int i = 1; i < m.nRows; ++i) {
        int j = i;
        while (j > 0 && criteriaArray[j - 1] > criteriaArray[j]) {
            swapF(&criteriaArray[j - 1], &criteriaArray[j]);
            swapRows(m, j - 1, j);

            j--;
        }
    }
}

void sortByDistances(matrix m){
    insertionSortRowsMatrixByRowCriteriaF(m, getDistance);
}

// 11 задача //

int getNSpecialElement(matrix m){
    int sumColArray[m.nCols];
    int colArray[m.nRows];
    for(int i = 0; i < m.nCols; i ++) {
        for (int j = 0; j < m.nRows; i++)
            colArray[i] = m.values[j][i];

        sumColArray[i] = getSum(colArray, m.nRows);
    }

    int counter = 0;
    for (int i = 0; i < m.nCols; i++)
        for (int j = 0; j < m.nRows; j++)
            if (sumColArray[i] - m.values[j][i] < sumColArray[i])
                counter++;

    return counter;
}