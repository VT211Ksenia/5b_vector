#include "libs/data_structures/vector/vector.h"
#include "libs/data_structures/matrix/matrix.h"




int main() {
    matrix a = getMemMatrix(3, 3);
    inputMatrix(a);

    insertionSortColsMatrixByColCriteria(a, getMin);

    outputMatrix(a);

    return 0;
}
