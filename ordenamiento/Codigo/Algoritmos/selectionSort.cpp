#include "selection_sort.h"
#include "utility.h"  

//Link al propietario del codigo: https://www.programiz.com/dsa/selection-sort
void selectionSort(int array[], int size) {
    for (int step = 0; step < size - 1; step++) {
        int min_idx = step;
        for (int i = step + 1; i < size; i++) {
            if (array[i] < array[min_idx])
                min_idx = i;
        }
        swap(&array[min_idx], &array[step]);
    }
}
