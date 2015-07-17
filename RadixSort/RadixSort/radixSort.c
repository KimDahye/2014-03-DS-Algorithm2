//
//  radixSort.c
//  RadixSort
//
//  Created by 김다혜 on 2014. 11. 24..
//  Copyright (c) 2014년 김다혜. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <math.h>

#define BOUND 9
#define DIGIT 3

void radixSort(int * arr, int size);
void countingSortByDigit(int * arr, int size, int digit);
void copyArray(int * arr, int * bufferArr, int size);
void printArray(int * arr, int size);
int isSorted(int * arr, int size);

int main(int argc, const char * argv[]) {
    int arr[] = {329, 457, 657, 839, 436, 720, 355};
    int size = sizeof(arr)/sizeof(int);
    radixSort(arr, size);
    printArray(arr, size);
    printf("isSorted: %d", isSorted(arr, size));
    return 0;
}


void radixSort(int * arr, int size) {
    int i;
    for(i = 1; i < DIGIT+1; i++) {
        countingSortByDigit(arr, size, i);
    }
}

void countingSortByDigit(int * arr, int size, int digit){
    //radixSort용 countingSort, bound = 9로 고정
    if(arr == NULL || size < 1 || digit < 1) {
        perror("args error");
        return;
    }
    
    int i;
    int res[size];
    int count[BOUND+1];
    memset(count, 0, (BOUND+1)*sizeof(int));
    for(i = 0; i < size; i++){
        count[(arr[i]/((int)pow(BOUND+1, digit-1)))%(BOUND+1)]++; //{arr[i]/(10^(digit-1))}%10
    }
    for(i = 1; i < BOUND+1; i++) count[i] = count[i-1] + count[i];
    for(i = size-1; i > -1; i--) {
        res[count[(arr[i]/((int)pow(BOUND+1, digit-1)))%(BOUND+1)]-1] = arr[i];
        count[(arr[i]/((int)pow(BOUND+1, digit-1)))%(BOUND+1)]--;
    }
    copyArray(res, arr, size);
}

void copyArray(int * arr, int * bufferArr, int size) {
    for(int i = 0; i < size; i++) {
        bufferArr[i] = arr[i];
    }
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

int isSorted(int * arr, int size) {
    if(arr == NULL || size < 1) {
        return 1;
    }
    int i;
    for(i = 1; i < size; i++){
        if(arr[i-1] > arr[i]){
            return 0;
        }
    }
    return 1;
}