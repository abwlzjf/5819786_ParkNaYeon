#include <stdio.h>
#include <stdlib.h>
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
#define SIZE 100

int comparisonCount = 0;
int moveCount = 0;
int isFirst = 0;
int rounds = 0;

void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;
    }
}

void printArray(int* array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%3d ", array[i]);
    }
    printf("\n");
}

void doMergeSort(int* array, int start, int end) {
    int size = end - start + 1;

    for (int width = 1; width < size; width *= 2) {
        for (int i = start; i < size + start; i += 2 * width) {
            int left = i;
            int mid = i + width - 1;
            int right = i + 2 * width - 1;

            if (mid >= size + start) break; // 중간값이 배열 끝을 넘으면 종료
            if (right >= size + start) right = size + start - 1; // 오른쪽 끝 변환

            merge(array, left, mid, right); // 병합
        }

        rounds++;
        if (rounds % 10 == 0 && isFirst == 0) {
            for (int i = 0; i < 10; i++) // 0~9값
                printf("%3d ", array[i]);
            printf("| ");
            for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++) // 중앙-1 ~ 중앙+10
                printf("%3d ", array[i]);
            printf("\n\n");
        }
    }
}

void merge(int* array, int left, int mid, int right) {
    int i = left;       // 왼쪽 배열 시작
    int j = mid + 1;    // 오른쪽 배열 시작
    int k = 0;          // 정렬된 배열
    int size = right - left + 1;
    int sorted[SIZE];   // 정렬된 결과를 임시로 저장할 배열

    // 병합
    while (i <= mid && j <= right) {
        comparisonCount++;
        if (array[i] <= array[j]) {
            sorted[k++] = array[i++];
        }
        else {
            sorted[k++] = array[j++];
        }
        moveCount++;
    }

    // 왼쪽 배열의 잔여 요소 복사
    while (i <= mid) {
        sorted[k++] = array[i++];
        moveCount++;
    }

    // 오른쪽 배열의 요소 복사
    while (j <= right) {
        sorted[k++] = array[j++];
        moveCount++;
    }

    // 정렬된 내용 -> 원래 배열로 복사
    for (int m = 0; m < size; m++) {
        array[left + m] = sorted[m];
        moveCount++;
    }
}