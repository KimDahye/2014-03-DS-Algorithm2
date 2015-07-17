//
//  findMaxSubarray.c
//  FindMaxSubarray
//
//  Created by 김다혜 on 2014. 11. 1..
//  Copyright (c) 2014년 김다혜. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct results {
    int low;
    int high;
    int sum;
} Results;

void test(int ** arrays, int arrlength, int * sizes, int * calculatedSum);
int isEqualResults(Results * res1, Results * res2);
int isEqualSum(int calSum, int dcSum);
Results * createResults(int low, int high, int sum);
Results * findMaxSubarray(int * arr, int low, int high);
Results * findMaxCrossingSubarray(int * arr, int low, int mid, int high);
Results * maxSumFromStartPos(int * arr, int start, int last, int direction);
Results * findMaxSubarrWithBruteForce(int * arr, int size);
Results * findMaxSubarrayLinear(int * arr, int size);

int main(int argc, const char * argv[]) {
    int arr1[] = {};
    int size1 = 0;
    int arr2[] = {-1};
    int size2 = sizeof(arr2)/sizeof(int);
    int arr3[] = {-1,1};
    int size3 = sizeof(arr3)/sizeof(int);
    int arr4[] = {1,5,-1,7};
    int size4 = sizeof(arr4)/sizeof(int);
    int arr5[] = {1,-1,2,3,4,5,6,-2,7,8,-3,9,10,-4,-5,-6,13,-8,-9,11};
    int size5 = sizeof(arr5)/sizeof(int);
    
    int * arrays[] = {arr1, arr2, arr3, arr4, arr5};
    int sizes[] = {size1, size2, size3, size4, size5};
    int calculatedSum[] = {0, -1, 1, 12, 49};
    
    test(arrays, sizeof(arrays) / sizeof(int *), sizes, calculatedSum);
    
    return 0;
}

void test(int ** arrays, int length, int * sizes, int * calculatedSum) {
    Results * res1 = NULL;
    Results * res2 = NULL;
    Results * res3 = NULL;
    
    for(int i = 0; i < length; i++) {
        res1 = findMaxSubarray(arrays[i], 0, sizes[i]-1);
        res2 = findMaxSubarrWithBruteForce(arrays[i], sizes[i]);
        res3 = findMaxSubarrayLinear(arrays[i], sizes[i]);
        printf("[arr%d]Comparison btw DC and BF: %d\n", i+1 , isEqualResults(res1, res2));
        printf("[arr%d]Comparison btw DC and Linear: %d\n", i+1 , isEqualResults(res1, res3));
        if(res1 != NULL && res2 != NULL) {
            printf("[arr%d]Comparison btw Person and DC: %d\n", i+1, isEqualSum(calculatedSum[i], res1->sum));
            printf("[arr%d]DC: low: %d, high: %d, sum: %d\n", i+1, res1->low, res1->high, res1->sum);
            printf("[arr%d]BF: low: %d, high: %d, sum: %d\n", i+1, res2->low, res2->high, res2->sum);
            printf("[arr%d]Linear: low: %d, high: %d, sum: %d\n", i+1, res3->low, res3->high, res3->sum);
        }else {
            printf("[arr%d]res1 & res2 are not found\n", i+1);
        }
    }
    
    free(res1);
    free(res2);
    free(res3);
}

int isEqualResults(Results * res1, Results * res2){
    if(res1 == NULL && res2 == NULL) return 1;
    
    if(res1 != NULL && res2 == NULL) return 0;
    if(res1 == NULL && res2 != NULL) return 0;
    if(res1->sum != res2->sum) return 0;
    
    return 1;
}

int isEqualSum(int calSum, int dcSum){
    if(calSum != dcSum) return 0;
    return 1;
}

Results * createResults(int low, int high, int sum) {
    Results * res = (Results *) malloc(sizeof(Results));
    if(!res){
        perror("malloc error");
        return NULL;
    }
    res->low = low;
    res->high = high;
    res->sum = sum;
    
    return res;
}

Results * findMaxSubarray(int * arr, int low, int high) {
    if(arr == NULL) return NULL;
    if(low > high) return NULL; //debugging - 현욱이가 추가해준 부분
    
    if(low == high) return createResults(low, high, arr[low]);
    
    int mid;
    Results * left;
    Results * right;
    Results * cross;
    
    mid = low + (high - low)/2;
    left = findMaxSubarray(arr, low, mid);
    right = findMaxSubarray(arr, mid+1, high);
    cross = findMaxCrossingSubarray(arr, low, mid, high);
    
    if(left->sum >= right->sum && left->sum >= cross->sum) {
        free(right);
        free(cross);
        return left;
    }
    if(right->sum >= left->sum && right->sum >= cross->sum) {
        free(left);
        free(cross);
        return right;
    }
    free(left);
    free(right);
    return cross;
}

Results * findMaxCrossingSubarray(int * arr, int low, int mid, int high) {
    if(arr == NULL) return NULL;
    
    Results * left;
    Results * right;
    int leftIndex, rightIndex, leftSum, rightSum;
    
    left = maxSumFromStartPos(arr, mid, low, -1);
    right = maxSumFromStartPos(arr, mid+1, high, 1);
    
    leftIndex = left->high;
    rightIndex = right->high;
    leftSum = left->sum;
    rightSum = right->sum;
    
    free(left);
    free(right);
    
    return createResults(leftIndex, rightIndex, leftSum + rightSum);
}

Results * maxSumFromStartPos(int * arr, int start, int last, int direction) {
    if(arr == NULL) return NULL;
    
    int max, acc, maxIndex, i;
    
    max = arr[start];
    acc = arr[start];
    maxIndex = start;
    i = start;
    
    while(i != last) { //debugging - last여야 하는데 start로 했었음
        i = i + direction;
        acc = acc + arr[i];
        if(acc > max) {
            max = acc;
            maxIndex = i;
        }
    }
    
    //direction 이 -1일 경우 low <= high 조건이 성립하지 않는다.
    return createResults(start, maxIndex, max);
}

Results * findMaxSubarrWithBruteForce(int * arr, int size) {
    if(arr == NULL || size == 0) return NULL;
    
    Results * max;
    Results * present;
    int i;
    
    max = maxSumFromStartPos(arr, 0, size-1, 1);
    present = maxSumFromStartPos(arr, 0, size-1, 1);
    
    for(i = 1; i<size; i++) {
        present = maxSumFromStartPos(arr, i, size-1, 1);
        if(present->sum > max->sum){
            max->sum = present->sum;
            max->low = present->low;
            max->high = present->high;
        }
    }
    
    free(present);
    return max;
}

Results * findMaxSubarrayLinear(int * arr, int size) {
    if(arr == NULL || size == 0) return NULL;
    
    int i;
    Results res[size];
    Results * max;
    
    res[0].low= 0;
    res[0].high = 0;
    res[0].sum = arr[0];
    
    for(i = 1; i < size; i++) {
        if(res[i-1].sum < 0) {
            res[i].low = i;
            res[i].sum = arr[i];
        }else {
            res[i].low = res[i-1].low;
            res[i].sum = res[i-1].sum + arr[i];
        }
        res[i].high = i;
    }
    
    max = createResults(res[0].low, res[0].high, res[0].sum);
    
    for(i = 1; i < size; i++) {
        if(max->sum < res[i].sum) {
            max->low = res[i].low;
            max->high = res[i].high;
            max->sum = res[i].sum;
        }
    }
    
    return max;
}




