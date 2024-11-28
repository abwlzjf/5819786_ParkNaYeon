#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SWAP(x, y, t)  ((t) = (x), (x) = (y), (y) = (t))
#define SIZE 100
#include "14-quicksort.h"

int comparisonCount = 0;
int moveCount = 0;
int totalComparisons = 0;
int totalMoveCount = 0;
int isFirst = 0;
int rounds = 0;

// 배열 출력 함수
void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// 랜덤 배열 생성 함수
void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;
    }
}

// 퀵 정렬의 분할 함수
int partition(int array[], int left, int right) {
    int pivot = array[right];  // 피벗을 배열의 마지막 요소로 선택
    int i = left - 1;
    int temp;

    for (int j = left; j <= right - 1; j++) {
        comparisonCount++;
        if (array[j] < pivot) {
            i++;
            SWAP(array[i], array[j], temp);
            moveCount += 3;
        }
    }
    SWAP(array[i + 1], array[right], temp);
    moveCount += 3;
    return i + 1;
}

void doQuickSort(int array[], int left, int right) {
    int stack[SIZE]; 
    int top = -1;

    // 초기 범위
    stack[++top] = left;
    stack[++top] = right;

    while (top >= 0) {
        // 스택에서 상위 요소 출력
        right = stack[top--];
        left = stack[top--];

        int pivot = partition(array, left, right);  // 배열 분할

        // 피벗의 왼쪽 부분
        if (pivot - 1 > left) {
            stack[++top] = left;
            stack[++top] = pivot - 1;
        }

        // 피벗의 오른쪽 부분
        if (pivot + 1 < right) {
            stack[++top] = pivot + 1;
            stack[++top] = right;
        }

        // 정렬 과정 출력
        if (rounds % 10 == 0 && isFirst == 0) {
            for (int i = 40; i < 60; i++) {
                printf("%d ", array[i]);
            }
            printf("\n\n");
        }
        rounds++;
    }
}