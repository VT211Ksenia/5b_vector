#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define TIME_TEST(testCode, time){ \
clock_t start_time = clock () ; \
testCode \
clock_t end_time = clock () ;\
clock_t sort_time = end_time - start_time ; \
time = ( double ) sort_time / CLOCKS_PER_SEC ; \
}


#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])

void outputArray_(int *arr, int size){
    for (int i = 0; i < size; ++i) {
        printf("%d", arr[i]);
    }
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int digit(int n, int k, int N, int M) {
    return (n >> (N * k) & (M - 1));
}

void radixSort_(int *a, int *n) {
    int bit = 8;
    int k = (32 + bit - 1) / bit;
    int M = 1 << bit;
    int sz = n - a;
    int *b = (int *) malloc(sizeof(int) * sz);
    int *c = (int *) malloc(sizeof(int) * M);
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < M; j++)
            c[j] = 0;

        for (int *j = a; j < n; j++)
            c[digit(*j, i, bit, M)]++;

        for (int j = 1; j < M; j++)
            c[j] += c[j - 1];

        for (int *j = n - 1; j >= a; j--)
            b[--c[digit(*j, i, bit, M)]] = *j;

        int cur = 0;
        for (int *j = a; j < n; j++)
            *j = b[cur++];
    }
    free(b);
    free(c);
}

void radixSort(int *a, size_t n) {
    radixSort_(a, a + n);
}

void BubbleSort (int *arr, int size){
    for (int i = 0; i < size; ++i)
        for (int j = i + 1; j < size; ++j)
            if (arr[i] > arr[j])
                swap(&arr[i], &arr[j]);
}

void InsertionSort (int *arr, int size){
    int element, posElement;
    for (int i = 0; i < size; ++i) {
        element = arr[i];
        posElement = i - 1;
        while (posElement >= 0 && arr[posElement] > element){
            arr[posElement + 1] = arr[posElement];
            posElement = posElement - 1;
        }
        arr[posElement + 1] = element;
    }
}

void SelectionSort (int *arr, int size){
    for (int i = 0; i < size; ++i) {
        int min = i;
        for (int j = i + 1; j < size; ++j) {
            if (arr[j] < arr[min])
                min = j;
        }
        swap(&arr[min], &arr[i]);
    }
}

void CombSort(int *arr, int size) {
    int step = size;
    int swapped = 1;
    while (step > 1 || swapped) {
        if (step > 1)
            step /= 1.24733;
        swapped = 0;
        for (int i = 0, j = i + step; j < size; ++i, ++j)
            if (arr[i] > arr[j]) {
                swap(&arr[i], &arr[j]);
                swapped = 1;
            }
    }
}

void ShellSort (int *arr, int size){
    int i, j, step;
    int temp;
    for (step = size / 2; step > 0; step /= 2 ) {
        for (i = step; i < size; i++) {
            temp = arr[i];
            for (j = i; j >= step; j -= step) {
                if (temp < arr[j - step])
                    arr[j] = arr[j - step];
                else
                    break;
            }
            arr[j] = temp;
        }
    }
}

long long getBubbleSortNComp(int *a, size_t n) {
    long long nComps = 0;
    for (size_t i = 0; ++nComps && i < n - 1; i++)
        for (size_t j = n - 1; ++nComps && j > i; j--)
            if (++nComps && a[j - 1] > a[j]) {
                swap(&a[j - 1], &a[j]);
            }
    return nComps;
}

long long getSelectionSortNComp(int *a, size_t n) {
    long long nComps = 0;
    for (int i = 0; ++nComps && i < n; i++) {
        int min = a[i];
        int minIndex = i;
        for (int j = i + 1; ++nComps && j < n; j++)
            if (++nComps && a[j] < min) {
                min = a[j];
                minIndex = j;
            }
        if (++nComps && i != minIndex)
            swap(&a[i], &a[minIndex]);
    }

    return nComps;
}

long long getInsertionSortNComp(int *a, size_t n) {
    long long nComps = 0;
    for (size_t i = 1; ++nComps && i < n; i++) {
        int t = a[i];
        size_t j = i;
        while (++nComps && j > 0 && a[j - 1] > t) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = t;
    }
    return nComps;
}

long long getCombSortNComp(int *a, size_t n) {
    size_t step = n;
    int swapped = 1;
    long long nComps = 0;
    while (++nComps && step > 1 || swapped) {
        if (++nComps && step > 1)
            step /= 1.24733;
        swapped = 0;
        for (size_t i = 0, j = i + step; ++nComps && j < n; ++i, ++j)
            if (++nComps && a[i] > a[j]) {
                swap(&a[i], &a[j]);
                swapped = 1;
            }
    }
    return nComps;
}

long long getShellSortNComp(int *a, size_t n) {
    long long nComps = 0;
    size_t j;
    int tmp;
    for (size_t step = n / 2; ++nComps && step > 0; step /= 2)
        for (size_t i = step; ++nComps && i < n; i++) {
            tmp = a[i];
            for (j = i; ++nComps && j >= step; j -= step) {
                if (++nComps && tmp < a[j - step])
                    a[j] = a[j - step];
                else
                    break;
            }
            a[j] = tmp;
        }
    return nComps;
}

long long getRadixSortNComps_(int *a, int *n) {
    long long nComps = 0;
    int bit = 8;
    int k = (32 + bit - 1) / bit;
    int M = 1 << bit;
    int sz = n - a;
    int *b = (int *) malloc(sizeof(int) * sz);
    int *c = (int *) malloc(sizeof(int) * M);
    for (int i = 0; ++nComps && i < k; i++) {
        for (int j = 0; ++nComps && j < M; j++)
            c[j] = 0;

        for (int *j = a; ++nComps && j < n; j++)
            c[digit(*j, i, bit, M)]++;

        for (int j = 1; ++nComps && j < M; j++)
            c[j] += c[j - 1];

        for (int *j = n - 1; ++nComps && j >= a; j--)
            b[--c[digit(*j, i, bit, M)]] = *j;

        int cur = 0;
        for (int *j = a; ++nComps && j < n; j++)
            *j = b[cur++];
    }
    free(b);
    free(c);
    return nComps;
}

void getRadixSortNComps(int *a, size_t n) {
    getRadixSortNComps_(a, a + n);
}

typedef struct SortFunc {
    void (*sort) (int *arr, int size);

    char arr[64];
} SortFunc;

typedef struct GeneratingFunc{
    void (*generate)(int *arr, int size);

    char arr[64];
} GeneratingFunc;

void generateOrderedArray (int *a, int size){
    for (int i = 0; i < size; ++i) {
        a[i] = i;
    }
}

void generateOrderedBackwards (int *a, int size){
    for (int i = 0; i < size; ++i) {
        a[i] = size - i;
    }
}

void generateRandomArray (int *a, int size){
    for (int i = 0; i < size; ++i) {
        a[i] = rand() % 10000;
    }
}

double getTime() {
    clock_t start_time = clock();

    clock_t end_time = clock();
    clock_t sort_time = end_time - start_time;
    return (double) sort_time / CLOCKS_PER_SEC;
}

bool isOrdered(int *arr, int size){
    for (int i = 1; i < size; ++i) {
        if (arr[i] < arr[i - 1])
            return false;
    }
    return true;
}

void checkTime (void (*sortFunc) (int *, int), void (*generateFunc) (int*, int), int size, char *experimentName) {
    static int runCounter = 1;
    static int innerBuffer[100000];
    generateFunc(innerBuffer, size);
    printf("Run #%d| ", runCounter++);
    printf("Name : %s\n", experimentName);

    double time;
    TIME_TEST({ sortFunc(innerBuffer, size); }, time)
// результаты замера
    printf(" Status : ");
    if (isOrdered(innerBuffer, size)) {
        printf("OK! Time: %.3f s.\n", time);
// запись в файл
        char filename[256];
        sprintf(filename, "./data/%s.csv", "experiment");
        FILE *f = fopen(filename, "a");
        if (f == NULL) {
            printf("FileOpenError %s", filename);
            exit(1);
        }
        fprintf(f, "%zu; %.3f\n", size, time);
        fclose(f);
    } else {
        printf("Wrong !\n");

// вывод массива, который не смог быть отсортирован
        outputArray_(innerBuffer, size);
        exit(1);
    }
}
//{SelectionSort, "SelectionSort"}
//  {InsertionSort, "InsertionSort"},
//  {ShellSort, "ShellSort"},
//  {BubbleSort, "BubbleSort"},
//  {CombSort, "CombSort"}

//{generateRandomArray, "random"} ,
//{generateOrderedArray, "ordered"} ,
//{generateOrderedBackwards, "orderedBackwards"}

void timeExperiment () {
// описание функций сортировки
    SortFunc sorts [] = {
            {radixSort, "radixSort"}




    };
    const unsigned FUNCS_N = ARRAY_SIZE(sorts);

// описание функций генерации
    GeneratingFunc generatingFuncs [] = {
            //{generateRandomArray, "random"} ,
            //{generateOrderedArray, "ordered"} ,
            {generateOrderedBackwards, "orderedBackwards"}
    };
    const unsigned CASES_N = ARRAY_SIZE(generatingFuncs);

// запись статистики в файл
    for (int size = 10000; size <= 100000; size += 10000) {
        printf ("><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n") ;
        printf (" Size : %d\n", size ) ;
        for (int i = 0; i < FUNCS_N ; i ++) {
            for (int j = 0; j < CASES_N ; j ++) {
// генерация имени файла
                static char filename [128];
                sprintf(filename, "%s_%s_time ", sorts[i].arr, generatingFuncs[j].arr);
                checkTime (sorts[i].sort, generatingFuncs[j].generate, size, filename);
            }
        }
        printf ("\n");
    }
}

double getTime1() {
    clock_t start_time = clock();
    int n = 200000;
    int a[n];
    generateRandomArray(a, n);
    for (int i = 0; i < n - 1; i++) {
        int minPos = i;
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[minPos])
                minPos = j;
        swap(&a[i], &a[minPos]);
    }
    clock_t end_time = clock();
    clock_t sort_time = end_time - start_time;
    return (double) sort_time / CLOCKS_PER_SEC;
}

int main() {
    printf("%lf", getTime1());

    return 0;
}
