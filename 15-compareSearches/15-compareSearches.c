#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
#define SIZE 1000

int compareCount = 0;
void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;
    }
}

void printArray(int* array) {
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++)
        printf("%3d ", array[i]);
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++)
        printf("%3d ", array[i]);
    printf("\n");
}

// 피벗 기준으로 배열 분할
int partition(int* array, int left, int right) {
    int pivot = array[left];
    int temp;
    int i = left + 1, j = right;

    while (1) {
        while (i <= right && array[i] <= pivot) {
            i++;
            compareCount++; // 비교 횟수 증가
        }
        while (j > left && array[j] >= pivot) {
            j--;
            compareCount++; // 비교 횟수 증가
        }
        if (i > j) break;
        SWAP(array[i], array[j], temp);
    }
    SWAP(array[left], array[j], temp); // 피벗을 올바른 위치로 이동
    return j;
}

// 퀵 정렬 수행 및 비교 횟수 계산
void quickSort(int* array, int left, int right) {
    if (left < right) {
        int pivotIndex = partition(array, left, right);
        quickSort(array, left, pivotIndex - 1); // 왼쪽 부분
        quickSort(array, pivotIndex + 1, right); // 오른쪽 부분
    }
}

// 퀵 정렬 수행 및 비교 횟수 반환
void getQuickSortCompareCount(int* array) {
    compareCount = 0;
    quickSort(array, 0, SIZE - 1);
}

// 순차 탐색
double getAverageLinearSearchCompareCount(int* array) {
    int totalCompareCount = 0;

    for (int i = 0; i < 100; i++) {
        int target = array[rand() % SIZE]; // 배열 내 목표값 선택
        int compareCount = 0;

        for (int j = 0; j < SIZE; j++) {
            compareCount++;
            if (array[j] == target) break;
        }
        totalCompareCount += compareCount;
    }
    return totalCompareCount / 100.0;
}

// 이진 탐색: 100번 수행 후 평균 비교 횟수 계산
double getAverageBinarySearchCompareCount(int* array) {
    int totalCompareCount = 0;

    for (int i = 0; i < 100; i++) {
        int target = array[rand() % SIZE]; // 배열 내 목표값 선택
        int left = 0, right = SIZE - 1, compareCount = 0;

        while (left <= right) {
            int mid = (left + right) / 2;
            compareCount++;
            if (array[mid] == target) break; // 값 찾으면 종료
            else if (array[mid] < target)
                left = mid + 1; // 오른쪽으로 이동
            else
                right = mid - 1; // 왼쪽으로 이동
        }
        totalCompareCount += compareCount;
    }
    return totalCompareCount / 100.0;
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    int array[SIZE];

    generateRandomArray(array);

    // 순차 탐색 평균 비교 횟수
    printf("Average Linear Search Compare Count: %.2f\n",
        getAverageLinearSearchCompareCount(array));

    // 퀵 정렬 수행 및 비교 횟수
    getQuickSortCompareCount(array);
    printf("Quick Sort Compare Count: %d\n", compareCount);

    // 이진 탐색 평균 비교 횟수
    printf("Average Binary Search Compare Count: %.2f\n\n",
        getAverageBinarySearchCompareCount(array));

    printArray(array);

    return 0;
}