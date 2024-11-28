#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
#define SIZE 1000

// �迭 ����
void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 10000;
    }
}

// �迭 ���
void printArray(int* array) {
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++)
        printf("%4d ", array[i]);
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++)
        printf("%4d ", array[i]);
    printf("\n\n");
}

// �� ������ ���� �Լ�
int partition(int array[], int left, int right) {
    int pivot, temp;
    int low, high;
    low = left;
    high = right + 1;
    pivot = array[left];

    do {
        do {
            low++;
        } while (low <= right && array[low] < pivot);

        do {
            high--;
        } while (high >= left && array[high] > pivot);

        if (low < high) {
            SWAP(array[low], array[high], temp);
        }
    } while (low < high);

    SWAP(array[left], array[high], temp);

    return high;
}

// �� ����
void QuickSort(int array[], int left, int right) {
    if (left < right) {
        int pivotIndex = partition(array, left, right);
        QuickSort(array, left, pivotIndex - 1);
        QuickSort(array, pivotIndex + 1, right);
    }
}

// ���� Ž��
int BinarySearch(int array[], int key) {
    int low = 0;
    int high = SIZE - 1;
    int comparisons = 0;

    while (low <= high) {
        int mid = (low + high) / 2;
        comparisons++;

        if (array[mid] == key) {
            return comparisons;  // ���� ã���� ��ȯ
            comparisons++;
        }

        else if (array[mid] < key) {
            comparisons++;
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return comparisons;
}

// ���� Ž��
int InterpolationSearch(int array[], int key) {
    int low = 0;
    int high = SIZE - 1;
    int comparisons = 0;

    while (low <= high && key >= array[low] && key <= array[high]) {
        if (low == high) {
            comparisons++;  // low == high ��
            if (array[low] == key) return comparisons;
            break;
        }
        // ���� Ž��
        int pos = low + (int)(((double)(high - low) / (array[high] - array[low])) * (key - array[low]));

        comparisons++; // array[pos] == key ��
        if (array[pos] == key) {
            return comparisons;
            comparisons++;
        }
        else if (array[pos] < key) {
            comparisons++; // array[pos] < key ��
            low = pos + 1;
        }
        else {
            high = pos - 1;
        }
    }
    return comparisons;
}

// ���� Ž�� ��� �� Ƚ��
double getAverageBinarySearchCompareCount(int* array) {
    int totalComparisons = 0;

    for (int i = 0; i < 1000; i++) {
        int target = array[rand() % SIZE];
        totalComparisons += BinarySearch(array, target);
    }
    return (double)totalComparisons / 1000;
}

// ���� Ž�� ��� �� Ƚ��
double getAverageInterpolationSearchCompareCount(int* array) {
    int totalComparisons = 0;

    for (int i = 0; i < 1000; i++) {
        int target = array[rand() % SIZE];
        totalComparisons += InterpolationSearch(array, target);
    }
    return (double)totalComparisons / 1000;
}