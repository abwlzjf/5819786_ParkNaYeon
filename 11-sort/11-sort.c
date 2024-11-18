#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
#define SIZE 100

void generateRandomData(int array[]) {
    srand(time(0));
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;
    }
}

void printArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// 선택 정렬
void doSelectionSort(int array[]) {
    int i, j, min, temp;
    printf("Selection Sort:\n");

    int tempArray[SIZE];
    for (i = 0; i < SIZE; i++) {
        tempArray[i] = array[i];
    }

    for (i = 0; i < SIZE - 1; i++) {
        min = i;
        for (j = i + 1; j < SIZE; j++) {
            if (tempArray[j] < tempArray[min]) {
                min = j;
            }
        }
        SWAP(tempArray[i], tempArray[min], temp);

        if ((i + 1) % 20 == 10 || i == SIZE - 2) {
            printf("\nStep %d: ", i + 1);
            printArray(tempArray);
        }
    }
}

// 삽입 정렬
void doInsertionSort(int array[]) {
    int CompareCountAverage = 0;

    for (int trial = 0; trial < 20; trial++) {
        int tempArray[SIZE];
        for (int i = 0; i < SIZE; i++) {
            tempArray[i] = array[i];
        }

        int compareCount = 0;
        for (int i = 1; i < SIZE; i++) {
            int key = tempArray[i];
            int j = i - 1;
            while (j >= 0 && tempArray[j] > key) {
                tempArray[j + 1] = tempArray[j];
                j--;
                compareCount++;
            }
            tempArray[j + 1] = key;
        }

        CompareCountAverage += compareCount;
    }

    // 평균 비교 횟수 출력
    printf("\n\nInsertion Sort Compare Average: %d\n", CompareCountAverage / 20);
    printf("Insertion Sort Result:\n");
    printArray(array);
}

// 버블 정렬
void doBubbleSort(int array[]) {
    int totalMoveCount = 0;

    for (int trial = 0; trial < 20; trial++) {
        int tempArray[SIZE];
        for (int i = 0; i < SIZE; i++) {
            tempArray[i] = array[i];
        }

        int moveCount = 0;
        for (int i = 0; i < SIZE - 1; i++) {
            for (int j = 0; j < SIZE - i - 1; j++) {
                if (tempArray[j] > tempArray[j + 1]) {
                    int temp;
                    SWAP(tempArray[j], tempArray[j + 1], temp);
                    moveCount += 3;
                }
            }
        }
        totalMoveCount += moveCount;
    }

    // 평균 이동 횟수 출력
    printf("\n\nBubble Sort Move Average: %d\n", totalMoveCount / 20);
    printf("Bubble Sort Result:\n");
    printArray(array);
}

int main() {
    int randomData[SIZE];
    generateRandomData(randomData);
 
    doSelectionSort(randomData);
    doInsertionSort(randomData);
    doBubbleSort(randomData);

    return 0;
}