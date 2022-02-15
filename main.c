#include "libs/data_structures/vector/vector.h"
#include "libs/data_structures/matrix/matrix.h"

void swapRowsWithMaxAndMinValue(matrix m) {
    position minIndex = getMinValuePos(m);
    position maxIndex = getMaxValuePos(m);
    if (minIndex.rowIndex != maxIndex.rowIndex)
        swapRows(m, minIndex.rowIndex, maxIndex.rowIndex);
}


int main() {
    matrix a = getMemMatrix(2, 2);
    inputMatrix(a);

    swapRows(a, 1, 2);

    outputMatrix(a);

    return 0;
}
