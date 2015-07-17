//
//  main.c
//  InsertSort
//
//  Created by 김다혜 on 2014. 10. 20..
//  Copyright (c) 2014년 김다혜. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

void printArray(int *array, int size);
void insert(int * array, int size);
void insertionSort(int * array, int size);
int isSorted(int * arr, int size);

int main(int argc, const char * argv[]) {
    //test case 초기화
    int arr1[] = {};
    int arr2[] = {1};
    int arr3[] = {2, 5};
    int arr4[] = {1,2,3,4,5,6,7,8,9,10};
    int arr5[] = {10,9,8,7,6,5,4,3,2,1};
    int arr6[] = {3,5,2,7,10,8,1,9,4,6};
    int arr7[] = {3,5,2,7,10,5,1,5,4,6};
    
    //삽입 정렬
    insertionSort(arr1, sizeof(arr1)/sizeof(int));
    insertionSort(arr2, sizeof(arr2)/sizeof(int));
    insertionSort(arr3, sizeof(arr3)/sizeof(int));
    insertionSort(arr4, sizeof(arr4)/sizeof(int));
    insertionSort(arr5, sizeof(arr5)/sizeof(int));
    insertionSort(arr6, sizeof(arr6)/sizeof(int));
    insertionSort(arr7, sizeof(arr7)/sizeof(int));

    //삽입정렬 후 오름차순이 맞는지 확인
    printf("%d, %d, %d, %d, %d, %d, %d\n", isSorted(arr1, sizeof(arr1)/sizeof(int)), isSorted(arr2, sizeof(arr2)/sizeof(int)), isSorted(arr3, sizeof(arr3)/sizeof(int)), isSorted(arr4, sizeof(arr4)/sizeof(int)), isSorted(arr5, sizeof(arr5)/sizeof(int)), isSorted(arr6, sizeof(arr6)/sizeof(int)), isSorted(arr7, sizeof(arr7)/sizeof(int)));

    return 0;
}

void printArray(int * array, int size) {
    for(int i = 0; i<size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void insert(int * array, int size){
    int key = array[size - 1];
    int index = size - 2;
    while(index >= 0 && array[index] > key){
        array[index + 1] = array[index];
        index--;
    }
    array[index + 1] = key;
}

void insertionSort(int * array, int size) {
    for(int index = 1; index < size; index++){
        int key = array[index];
        int subindex = index - 1;
        while(subindex >= 0 && array[subindex] > key){
            array[subindex+1] = array[subindex];
            subindex--;
        }
        array[subindex + 1] = key;
    }
}

int isSorted(int * arr, int size){
    for(int index = 0; index < size-1; index++){
        if(arr[index] > arr[index+1]){
            return 0;
        }
    }
    return 1;
}
