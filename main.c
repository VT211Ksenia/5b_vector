#include "libs/data_structures/vector/vector.h"
#include "libs/data_structures/matrix/matrix.h"

void test_pushBack_notEmpty(){
    vector v = createVector(5);
    pushBack(&v, 10);

    assert(v.size == 1);

    popBack(&v);
    assert(v.size == 0);
    assert(v.capacity == 5);

    clear(&v);
}
void test_pushBack_isEmpty(){
    vector v = createVector(0);
    pushBack(&v, 2);

    assert(v.size == 1);

    popBack(&v);
    assert(v.size == 0);
    assert(v.capacity == 1);
}

void test_atVector_notEmpty(){
    vector v = createVector(0);
    pushBack(&v, 30);
    pushBack(&v, 40);
    pushBack(&v, 50);

    assert(atVector(&v, 0) == &v.data[0]);
    assert(atVector(&v, 1) == &v.data[1]);
    assert(atVector(&v, 2) == &v.data[2]);
}

void test_atVector_requestToLastElement(){
    vector v = createVector(0);
    pushBack(&v, 322);

    assert(atVector(&v, 0) == &v.data[0]);
}

void test_back_oneElementInVector(){
    vector v = createVector(0);
    pushBack(&v, 321);

    assert(back(&v) == &v.data[0]);
}

void test_front_oneElementInVector(){
    vector v = createVector(0);
    pushBack(&v, 321);

    assert(front(&v) == &v.data[0]);
}

int main() {
    matrix a = getMemMatrix(2, 2);
    inputMatrix(a);

    swapRows(a, 1, 2);

    outputMatrix(a);

    return 0;
}
