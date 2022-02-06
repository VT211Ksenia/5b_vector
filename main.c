#include "libs/data_structures/vector/vector.h"

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


int main() {
    test_pushBack_notEmpty();
    test_pushBack_isEmpty();


    return 0;
}
