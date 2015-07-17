//
//  selectKthOrder.c
//  SelectKthOrder
//
//  Created by 김다혜 on 2014. 11. 26..
//  Copyright (c) 2014년 김다혜. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define ERROR_CODE -1

int * createRandomArray(int size);
void quickSort(int * arr, int start, int end);
int selectKthOrder(int * arr, int start, int end, int k);
int randomizedPartition(int * arr, int start, int end);
int partition(int * arr, int start, int end);
int randMinMax(int min, int max);
int isSame(int a, int b);
void printArray(int * arr, int size);

int main(int argc, const char * argv[]) {
    int size, k, val, valAfterSorting;
    int * arr;
    
    for(size = 1; size < 11; size++) {
        arr = createRandomArray(size);
        printArray(arr, size);
        
        k = randMinMax(0, size-1);
        val = selectKthOrder(arr, 0, size-1, k);
        printArray(arr, size);
        printf("k: %d, val: %d\n", k, val);
        
        quickSort(arr,0, size-1);
        valAfterSorting = arr[k];
        printArray(arr, size);
        printf("arr[k]: %d\n", valAfterSorting);
        printf("isSame: %d\n", isSame(val, valAfterSorting));
        free(arr);
        printf("-------------------------------------\n");
    }
    return 0;
}

int * createRandomArray(int size) {
    int * res = malloc(size * sizeof(int));
    int i;
    for(i = 0; i < size; i++) {
        res[i] = randMinMax(0, 20);
    }
    return res;
}

void quickSort(int * arr, int start, int end){
    if(arr == NULL) {
        perror("args error");
    }
    
    if(start < end){
        int pivot = randomizedPartition(arr, start, end);
        quickSort(arr, start, pivot - 1);
        quickSort(arr, pivot + 1, end);
    }
}

int selectKthOrder(int * arr, int start, int end, int k) {
    if(arr == NULL || start > end || k < start || k > end) {
        perror("args error");
        return -1;
    }
    
    int pivot = randomizedPartition(arr, start, end);
    if(pivot > k) return selectKthOrder(arr, start, pivot-1, k);
    if(pivot < k) return selectKthOrder(arr, pivot+1, end, k);
    return arr[pivot];
}
    
int randomizedPartition(int * arr, int start, int end){
    if(arr == NULL || start > end) {
        perror("args error");
        return ERROR_CODE;
    }
    
    int pivotIndex = randMinMax(start, end);
    int temp = arr[pivotIndex];
    arr[pivotIndex] = arr[end];
    arr[end] = temp;
    
    return partition(arr, start, end);
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

int randMinMax(int min, int max) {
    if(min > max) {
        perror("args error @randMinMax");
        return -1;
    }
    if(min == max) return min;
    return (rand() % max) + min; //[min, max-1+min] 중 리턴
}

int isSame(int a, int b) {
    if(a == b) return 1;
    return 0;
}

void printArray(int * arr, int size) {
    if(arr == NULL || size == 0) return;
    int i;
    printf("{ ");
    for(i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("}\n");
}