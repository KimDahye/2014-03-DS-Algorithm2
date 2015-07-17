//
//  main.c
//  MergeSort
//
//  Created by 김다혜 on 2014. 10. 22..
//  Copyright (c) 2014년 김다혜. All rights reserved.
//

#include <stdio.h>

/* 함수 선언 */
int mergeSort(int * arr, int size, int start, int end);
int merge(int * arr, int * bufferArr, int firstBegin, int firstLast, int scdLast);
void copy(int * arr, int * bufferArr, int start, int end);
int isSorted(int * arr, int size);
void printArray(int * array, int size);
void test(int ** arrays, int length, int * sizes);

/* main */
int main(int argc, const char * argv[]) {

    int arr1[] = {};
    int size1 = sizeof(arr1)/sizeof(int);
    int arr2[] = {1};
    int size2 = sizeof(arr2)/sizeof(int);
    int arr3[] = {3,2};
    int size3 = sizeof(arr3)/sizeof(int);
    int arr4[] = {1,2,3,4,5,6,7,8,9,10};
    int size4 = sizeof(arr4)/sizeof(int);
    int arr5[] = {10,9,8,7,6,5,4,3,2,1};
    int size5 = sizeof(arr5)/sizeof(int);
    int arr6[] = {7,1,4,8,2,9,10,3,6,5};
    int size6 = sizeof(arr6)/sizeof(int);
    int arr7[] = {7,5,4,7,6,1,2,10,2,8};
    int size7 = sizeof(arr7)/sizeof(int);
    
    int * arrays[] = {arr1, arr2, arr3, arr4, arr5, arr6, arr7};
    int sizes[] = {size1, size2, size3, size4, size5, size6, size7};
    test(arrays, sizeof(arrays) / sizeof(int *), sizes);
    
    return 0;
    
}

void test(int ** arrays, int length, int * sizes) {
    int result = 0;
    for(int i = 0; i < length; i++) {
        result = mergeSort(arrays[i], sizes[i], 0, sizes[i] - 1);
        printf("result of arr%d: %d, inversions = %d\n", i+1 , isSorted(arrays[i], sizes[i]), result);
        printArray(arrays[i], sizes[i]);
    }
}

int mergeSort(int * arr, int size, int start, int end) {
    int p, q, a, b, c;
    a = 0;
    b = 0;
    c = 0;
    
    int bufferArr[size];
    if(start < end) {
        p = start;
        q = start + (end-start)/2;
        a = mergeSort(arr, size, p, q);
        b = mergeSort(arr, size, q+1, end);
        c = merge(arr, bufferArr, p, q, end);
    }
    
    return a+b+c;
}

int merge(int * arr, int * bufferArr, int firstBegin, int firstLast, int scdLast) {
    int idx, arr1Idx, arr2Idx, count;
    
    copy(arr, bufferArr, firstBegin, scdLast);
    arr1Idx = firstBegin;
    arr2Idx = firstLast + 1;
    count = 0;
    
    for(idx = firstBegin; idx <= scdLast; idx++) {
        if (arr1Idx > firstLast) {
            arr[idx] = bufferArr[arr2Idx++];
        }else if (arr2Idx > scdLast) {
            arr[idx] = bufferArr[arr1Idx++];
        }else if (bufferArr[arr1Idx] < bufferArr[arr2Idx]) {
            arr[idx] = bufferArr[arr1Idx++];
        }else {
            arr[idx] = bufferArr[arr2Idx++];
            count = count + firstLast - arr1Idx + 1;
        }
    }
    
    return count;
}

void copy(int * arr, int * bufferArr, int start, int end) {
    for(int i = start; i <= end; i++) {
        bufferArr[i] = arr[i];
    }
}

int isSorted(int * arr, int size) {
    for(int index = 0; index < size-1; index++){
        if(arr[index] > arr[index+1]){
            return 0;
        }
    }
    return 1;
}

void printArray(int * array, int size) {
    for(int i = 0; i<size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}
