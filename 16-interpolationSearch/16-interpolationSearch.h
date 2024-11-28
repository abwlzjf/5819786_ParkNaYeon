#pragma once
extern void printArray(int *array);
extern void generateRandomArray(int* array);
extern void QuickSort(int array[], int left, int right);
extern int partition(int array[], int left, int right);
double getAverageBinarySearchCompareCount(int* array);
double getAverageInterpolationSearchCompareCount(int* array);