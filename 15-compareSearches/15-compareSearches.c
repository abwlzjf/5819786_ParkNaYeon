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

// �ǹ� �������� �迭 ����
int partition(int* array, int left, int right) {
    int pivot = array[left];
    int temp;
    int i = left + 1, j = right;

    while (1) {
        while (i <= right && array[i] <= pivot) {
            i++;
            compareCount++; // �� Ƚ�� ����
        }
        while (j > left && array[j] >= pivot) {
            j--;
            compareCount++; // �� Ƚ�� ����
        }
        if (i > j) break;
        SWAP(array[i], array[j], temp);
    }
    SWAP(array[left], array[j], temp); // �ǹ��� �ùٸ� ��ġ�� �̵�
    return j;
}

// �� ���� ���� �� �� Ƚ�� ���
void quickSort(int* array, int left, int right) {
    if (left < right) {
        int pivotIndex = partition(array, left, right);
        quickSort(array, left, pivotIndex - 1); // ���� �κ�
        quickSort(array, pivotIndex + 1, right); // ������ �κ�
    }
}

// �� ���� ���� �� �� Ƚ�� ��ȯ
void getQuickSortCompareCount(int* array) {
    compareCount = 0;
    quickSort(array, 0, SIZE - 1);
}

// ���� Ž��
double getAverageLinearSearchCompareCount(int* array) {
    int totalCompareCount = 0;

    for (int i = 0; i < 100; i++) {
        int target = array[rand() % SIZE]; // �迭 �� ��ǥ�� ����
        int compareCount = 0;

        for (int j = 0; j < SIZE; j++) {
            compareCount++;
            if (array[j] == target) break;
        }
        totalCompareCount += compareCount;
    }
    return totalCompareCount / 100.0;
}

// ���� Ž��: 100�� ���� �� ��� �� Ƚ�� ���
double getAverageBinarySearchCompareCount(int* array) {
    int totalCompareCount = 0;

    for (int i = 0; i < 100; i++) {
        int target = array[rand() % SIZE]; // �迭 �� ��ǥ�� ����
        int left = 0, right = SIZE - 1, compareCount = 0;

        while (left <= right) {
            int mid = (left + right) / 2;
            compareCount++;
            if (array[mid] == target) break; // �� ã���� ����
            else if (array[mid] < target)
                left = mid + 1; // ���������� �̵�
            else
                right = mid - 1; // �������� �̵�
        }
        totalCompareCount += compareCount;
    }
    return totalCompareCount / 100.0;
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    int array[SIZE];

    generateRandomArray(array);

    // ���� Ž�� ��� �� Ƚ��
    printf("Average Linear Search Compare Count: %.2f\n",
        getAverageLinearSearchCompareCount(array));

    // �� ���� ���� �� �� Ƚ��
    getQuickSortCompareCount(array);
    printf("Quick Sort Compare Count: %d\n", compareCount);

    // ���� Ž�� ��� �� Ƚ��
    printf("Average Binary Search Compare Count: %.2f\n\n",
        getAverageBinarySearchCompareCount(array));

    printArray(array);

    return 0;
}