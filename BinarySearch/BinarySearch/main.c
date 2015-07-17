//
//  main.c
//  BinarySearch
//
//  Created by 김다혜 on 2014. 10. 18..
//  Copyright (c) 2014년 김다혜. All rights reserved.
//

#include <stdio.h>

int binarySearch(int * arr, int length, int key);
int binarySearchLeftmost(int * arr, int length, int key);
int binarySearchRightmost(int * arr, int length, int key);
int howManyKeysInArray(int * arr, int length, int key);

int main(int argc, const char * argv[]) {
    int arr1[0] = {};
    int arr2[1] = {1};
    int arr3[2] = {3,5};
    int arr4[] = {3,5,5,5,6,7,7,9};
    
    printf("%d\n", binarySearch(arr1, sizeof(arr1)/sizeof(int), 0));
    printf("%d\n", binarySearch(arr2, sizeof(arr2)/sizeof(int), 1));
    printf("%d\n", binarySearch(arr3, sizeof(arr3)/sizeof(int), 5));
    printf("%d\n", binarySearch(arr4, sizeof(arr4)/sizeof(int), 7));

    printf("the number of 5 is %d\n", howManyKeysInArray(arr4, sizeof(arr4)/sizeof(int), 5));
    printf("the number of 7 is %d\n", howManyKeysInArray(arr4, sizeof(arr4)/sizeof(int), 7));
    printf("the number of 0 is %d\n", howManyKeysInArray(arr1, sizeof(arr1)/sizeof(int), 0));
    printf("the number of 4 is %d\n", howManyKeysInArray(arr4, sizeof(arr4)/sizeof(int), 4));
    printf("the number of 1 is %d \n", howManyKeysInArray(arr2, sizeof(arr2)/sizeof(arr2), 1));
    return 0;

}

int binarySearch(int * arr, int length, int key) {
    int left, right, middle;
    
    left = 0;
    right = length - 1;
    
    while(left <= right) {
        middle = left + (right - left)/2 ; // 엄밀하게는 (left+right)/2; 와는 다르다. left+ritht > upperbound 일 수 있기 때문.
        if(arr[middle] == key) return middle;
        else if(arr[middle] > key) right = middle - 1;
        else left = middle + 1;
    }
    
    return -1;
}

int binarySearchLeftmost(int * arr, int length, int key) {
    if(length == 0) return -1;
    
    int left, right, middle;
    
    left = 0;
    right = length - 1;
    
    while(left < right) {
        middle = left + (right - left)/2 ;
        if(arr[middle] >= key) right = middle;
        else left = middle + 1;
    }
    
    if(arr[left] == key) return left;
    return -1;
}

int binarySearchRightmost(int * arr, int length, int key) {
    if(length == 0) return -1;

    int left, right, middle;
    
    left = 0;
    right = length - 1;
    
    while(left < right) {
        if((right - left) % 2 == 0) middle = left + (right - left)/2;
        else middle = left + (right - left)/2 + 1;
       
        if(arr[middle] <= key) left = middle;
        else right = middle - 1;
        

    }
    
    if(arr[right] == key) return right;
    return -1;
}

int howManyKeysInArray(int * arr, int length, int key){
    int leftIndex, rightIndex;
    leftIndex = binarySearchLeftmost(arr, length, key);
    rightIndex = binarySearchRightmost(arr, length, key);

    if(leftIndex > -1) return rightIndex - leftIndex + 1;
    return 0;
}