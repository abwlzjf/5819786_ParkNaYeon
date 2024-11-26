#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "13-mergesort.h"

int totalComparisons = 0;
int totalMoves = 0;

int main() {
    srand(time(NULL));
    int array[SIZE];

    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);
        comparisonCount = 0;
        moveCount = 0;

        if (i == 0) {
            printf("Merge Sort Run\n");
            doMergeSort(array, 0, SIZE - 1);

            printf("Result\n");
            printArray(array, SIZE);
            isFirst++;
        }
        else {
            doMergeSort(array, 0, SIZE - 1);
        }

        totalComparisons += comparisonCount;
        totalMoves += moveCount;
    }

    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);

    return 0;
}