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

            if (mid >= size + start) break; // �߰����� �迭 ���� ������ ����
            if (right >= size + start) right = size + start - 1; // ������ �� ��ȯ

            merge(array, left, mid, right); // ����
        }

        rounds++;
        if (rounds % 10 == 0 && isFirst == 0) {
            for (int i = 0; i < 10; i++) // 0~9��
                printf("%3d ", array[i]);
            printf("| ");
            for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++) // �߾�-1 ~ �߾�+10
                printf("%3d ", array[i]);
            printf("\n\n");
        }
    }
}

void merge(int* array, int left, int mid, int right) {
    int i = left;       // ���� �迭 ����
    int j = mid + 1;    // ������ �迭 ����
    int k = 0;          // ���ĵ� �迭
    int size = right - left + 1;
    int sorted[SIZE];   // ���ĵ� ����� �ӽ÷� ������ �迭

    // ����
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

    // ���� �迭�� �ܿ� ��� ����
    while (i <= mid) {
        sorted[k++] = array[i++];
        moveCount++;
    }

    // ������ �迭�� ��� ����
    while (j <= right) {
        sorted[k++] = array[j++];
        moveCount++;
    }

    // ���ĵ� ���� -> ���� �迭�� ����
    for (int m = 0; m < size; m++) {
        array[left + m] = sorted[m];
        moveCount++;
    }
}