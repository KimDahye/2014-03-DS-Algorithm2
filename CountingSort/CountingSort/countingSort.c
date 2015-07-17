//
//  countingSort.c
//  CountingSort
//
//  Created by 김다혜 on 2014. 11. 24..
//  Copyright (c) 2014년 김다혜. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BOUND 20
#define DIGIT 3

void countingSort(int * arr, int * res, int size, int bound);
int * createRandomArray(int size);
int randMinMax(int min, int max);
void printArray(int * arr, int size);
int isSorted(int * arr, int size);

int main(int argc, const char * argv[]) {
    int * arr;
    int * res;
    int i;
    for(i = 0; i < 11; i++) {
        arr = createRandomArray(i);
        res = createRandomArray(i);
        printArray(arr, i);
        countingSort(arr, res, i, BOUND);
        printArray(res, i);
        printf("isSorted: %d\n", isSorted(res, i));
        printf("---------------------------\n");
        free(arr);
        free(res);
    }
    
    return 0;
}


void countingSort(int * arr, int * res, int size, int bound){
    if(arr == NULL || res == NULL || size < 1 || bound < 0) {
        perror("args error");
        return;
    }
    
    int i;
    int count[bound+1];
    memset(count, 0, (bound+1)*sizeof(int));
    for(i = 0; i < size; i++) count[arr[i]]++;
    for(i = 1; i < bound+1; i++) count[i] = count[i-1] + count[i];
    for(i = size-1; i > -1; i--) {
        res[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
}

int * createRandomArray(int size) {
    int * res = malloc(size * sizeof(int));
    int i;
    for(i = 0; i < size; i++) {
        res[i] = randMinMax(0, BOUND);
    }
    return res;
}

int randMinMax(int min, int max) {
    return (rand() % max) + min; //[min, max-1+min] 중 리턴
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

