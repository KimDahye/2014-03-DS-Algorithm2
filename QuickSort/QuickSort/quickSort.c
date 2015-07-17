//
//  quickSort.c
//  QuickSort
//
//  Created by 김다혜 on 2014. 11. 19..
//  Copyright (c) 2014년 김다혜. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define ERROR_CODE -1

void quickSort(int * arr, int start, int end);
void testQuickSort();
int partition(int * arr, int start, int end);
void testPartition();
int * createArrayRandomly(int size);
void printArray(int * arr, int size);
int isPartitioned(int * arr, int size, int pivot);
int isSorted(int * arr, int size);
int randMinMax(int min, int max);

int main(int argc, const char * argv[]) {
    testPartition();
    testQuickSort();
    return 0;
}

void quickSort(int * arr, int start, int end){
    if(arr == NULL) {
        perror("args error");
    }
    
    if(start < end){
        int pivot = partition(arr, start, end);
        quickSort(arr, start, pivot - 1);
        quickSort(arr, pivot + 1, end);
    }
}

void testQuickSort(){
    int size;
    int * arr;
    int sortedArray1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int sortedArray2[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int size1 = sizeof(sortedArray1)/sizeof(int);
    int size2 = sizeof(sortedArray2)/sizeof(int);
    
    for(size = 1; size < 17; size++) {
        arr = createArrayRandomly(size);
        printArray(arr, size);
        quickSort(arr, 0, size - 1);
        printf("[after quickSort]");
        printArray(arr, size);
        printf("isSorted: %d\n", isSorted(arr, size));
        printf("-------------------------------------------------------\n");
        free(arr);
    }
    
    printf("[test of sorted arrays]\n");
    
    printArray(sortedArray1, size1);
    quickSort(sortedArray1, 0, size1 - 1);
    printf("[after quickSort]");
    printArray(sortedArray1, size1);
    printf("isSorted: %d\n", isSorted(sortedArray1, size1));
    
    printArray(sortedArray2, size2);
    quickSort(sortedArray2, 0, size2 - 1);
    printf("[after quickSort]");
    printArray(sortedArray2, size2);
    printf("isSorted: %d\n", isSorted(sortedArray2, size2));
}

int partition(int * arr, int start, int end) {
    if(arr == NULL || start > end) {
        perror("args error");
        return ERROR_CODE;
    }
    int lastOfSmallBlock, key, curPosToBeChecked, temp;
    lastOfSmallBlock = start - 1;
    key = arr[end];
    for(curPosToBeChecked = start; curPosToBeChecked < end; curPosToBeChecked++) {
        if(arr[curPosToBeChecked] <= key) {
            lastOfSmallBlock++;
            temp = arr[curPosToBeChecked];
            arr[curPosToBeChecked] = arr[lastOfSmallBlock];
            arr[lastOfSmallBlock] = temp;
        }
    }
    arr[end] = arr[lastOfSmallBlock + 1];
    arr[lastOfSmallBlock + 1] = key;
    return lastOfSmallBlock + 1;
}

void testPartition(){
    int size, pivot;
    int * arr;
    int sortedArray1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int sortedArray2[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int size1 = sizeof(sortedArray1)/sizeof(int);
    int size2 = sizeof(sortedArray2)/sizeof(int);
    
    for(size = 1; size < 33; size++) {
        arr = createArrayRandomly(size);
        printArray(arr, size);
        pivot = partition(arr, 0, size - 1);
        printf("[after partition]");
        printArray(arr, size);
        printf("isPartitioned: %d\n", isPartitioned(arr, size, pivot));
        printf("-------------------------------------------------------\n");
        free(arr);
    }
    
    printf("[test of sorted arrays]\n");
    
    printArray(sortedArray1, size1);
    pivot = partition(sortedArray1, 0, size1 - 1);
    printf("[after partition]");
    printArray(sortedArray1, size1);
    printf("isPartitioned: %d\n", isPartitioned(sortedArray1, size1, pivot));
    
    printArray(sortedArray2, size2);
    pivot = partition(sortedArray2, 0, size2 - 1);
    printf("[after partition]");
    printArray(sortedArray2, size2);
    printf("isPartitioned: %d\n\n", isPartitioned(sortedArray2, size2, pivot));
}

int * createArrayRandomly(int size){
    int i;
    int * res = malloc(sizeof(int) * size);
    for(i = 0; i < size; i++) {
        res[i] = randMinMax(1, 20);
    }
    return res;
}

void printArray(int * arr, int size) {
    int i;
    printf("current array: { ");
    for(i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("}\n");
}

int isPartitioned(int * arr, int size, int pivot){
    int i;
    for(i = 0; i < pivot; i++) {
        if(arr[i] > arr[pivot]) return 0;
    }
    for(i = pivot + 1; i < size; i++){
        if(arr[i] <= arr[pivot]) return 0;
    }
    return 1;
}

int isSorted(int * arr, int size){
    int index;
    for(index = 0; index < size - 1; index++){
        if(arr[index] > arr[index + 1]){
            return 0;
        }
    }
    return 1;
}

int randMinMax(int min, int max) {
    return (rand() % max) + min; //[min, max-1+min] 중 리턴
}