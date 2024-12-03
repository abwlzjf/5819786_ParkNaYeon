#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100

void generateRandomNumbers(int array[]) {
    srand(time(0));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 1000;
    }
}

void printArray(int array[],int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    if (size != ARRAY_SIZE)
        printf("...");
    printf("\n\n");
}

void doShellSort(int array[], int gapType, int* comparisonCount, int* moveCount) {
    int tempArray[ARRAY_SIZE];
    int gap, i, j, temp;
    *comparisonCount = 0;
    *moveCount = 0;

    for (i = 0; i < ARRAY_SIZE; i++) {
        tempArray[i] = array[i];
    }
    if (gapType == 2)
        gap = ARRAY_SIZE / 2;
    else
        gap = ARRAY_SIZE / 3;

    while (gap >= 1) {
        printf("Sorting with gap = %d:\n", gap);
        for (i = gap; i < ARRAY_SIZE; i++) {
            temp = tempArray[i];
            j = i;

            while (j >= gap && tempArray[j - gap] > temp) {
                tempArray[j] = tempArray[j - gap];
                j -= gap;
                (*comparisonCount)++;
                (*moveCount)++;
            }
            tempArray[j] = temp;
            if (j != i) {
                (*moveCount)++;
            }
        }
        printArray(tempArray, 20);
        gap /= gapType;
    }
    printf("Sorted shellArray (gap = %d): \n", gapType);
    printArray(tempArray, ARRAY_SIZE);
}

void doInsertionSort(int array[], int* comparisonCount, int* moveCount) {
    int tempArray[ARRAY_SIZE];
    int i, j, key;

    *comparisonCount = 0;
    *moveCount = 0;

    for (i = 0; i < ARRAY_SIZE; i++) {
        tempArray[i] = array[i];
    }
    for (i = 1; i < ARRAY_SIZE; i++) {
        key = tempArray[i];
        j = i - 1;
        while (j >= 0 && tempArray[j] > key) {
            tempArray[j + 1] = tempArray[j];
            j--;
            (*comparisonCount)++;
            (*moveCount)++;
        }
        tempArray[j + 1] = key;
        if (j + 1 != i) {
            (*moveCount)++;
        }
    }
    printf("Sorted insertionArray: ");
    printArray(tempArray, ARRAY_SIZE);
}

int main() {
    int array[ARRAY_SIZE];
    int comparisonCount, moveCount;

    generateRandomNumbers(array);

    printf("Shell Sort (n/2):\n");
    doShellSort(array, 2, &comparisonCount, &moveCount);
    printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    printf("Shell Sort (n/3):\n");
    doShellSort(array, 3, &comparisonCount, &moveCount);
    printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    printf("Insertion Sort:\n");
    doInsertionSort(array, &comparisonCount, &moveCount);
    printf("Insertion Sort - Comparisons: %d, Moves: %d\n", comparisonCount, moveCount);

    return 0;
}