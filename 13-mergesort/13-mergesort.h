#pragma once
#define SIZE 100
extern void printArray(int array[], int size);
extern void generateRandomArray(int array[]);
extern void doMergeSort(int list[], int left, int right);
extern void merge(int list[], int left, int mid, int right);
extern int comparisonCount;
extern int moveCount;
extern int isFirst;
extern int rounds;