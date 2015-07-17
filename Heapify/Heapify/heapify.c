//
//  main.c
//  HeapSort
//
//  Created by 김다혜 on 2014. 11. 13..
//  Copyright (c) 2014년 김다혜. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct heap {
    int size;
    int capacity;
    int * element;
} heap_t;

void testHeapify();
void maxHeapify(heap_t * heap, int pos);
int isMaxHeap(heap_t * heap, int pos);
void printHeap(heap_t * heap, int pos, int level);
heap_t * makeSampleHeap(int n);
heap_t * makeSampleHeapManually();
int randMinMax(int min, int max);

int main(int argc, const char * argv[]) {
    testHeapify();
    return 0;
}

void testHeapify(){
    heap_t * heap = NULL;
    int sizes[] = {0,1,2,3,4,10};
    int testCount = sizeof(sizes)/sizeof(int);
    int i;
    
    for(i = 0; i < testCount + 1; i++) {
        if(i < testCount) {
            heap = makeSampleHeap(sizes[i]);
        }else {
            heap = makeSampleHeapManually();
        }
        printf("isMaxHeap: %d\n",isMaxHeap(heap, 1));
        printHeap(heap, 1, 0);
        
        maxHeapify(heap, 1);
        printf("isMaxHeap: %d\n",isMaxHeap(heap, 1));
        printHeap(heap, 1, 0);
        printf("-----------------------------------\n");
        
        free(heap->element);
        free(heap);
    }
}

void maxHeapify(heap_t * heap, int pos) {
    if(heap == NULL || heap->element == NULL || heap->size < 1) return;
    if(pos > heap->size) return;
    if(!isMaxHeap(heap, 2*pos) || !isMaxHeap(heap, 2*pos+1)){
        printf("argumnets error in maxHeapify\n");
        return;
    }
    
    int left, right, maxPos, temp;
    
    left = 2 * pos;
    right = 2 * pos + 1;
    if(left <= heap->size && heap->element[left] > heap->element[pos]) {
        maxPos = left;
    }else {
        maxPos = pos;
    }
    
    if(right <=heap->size && heap->element[right] > heap->element[maxPos]){
        maxPos = right;
    }
    
    if(pos != maxPos) {
        temp = heap->element[pos];
        heap->element[pos] = heap->element[maxPos];
        heap->element[maxPos] = temp;
        maxHeapify(heap, maxPos);
    }
}

int isMaxHeap(heap_t * heap, int pos) {
    if(heap == NULL || heap->element == NULL || heap->size < 1) return 1;
    if(pos > heap->size) return 1;
    
    int left, right;
    left = 2 * pos;
    right = 2 * pos + 1;
    
    if(left <= heap->size && heap->element[pos] < heap->element[left])
        return 0;
    if(right <= heap->size && heap->element[pos] < heap->element[right])
        return 0;
    return isMaxHeap(heap, left) && isMaxHeap(heap, right);
}

void printHeap(heap_t * heap, int pos, int level) {
    if(heap == NULL || heap->element == NULL || heap->size < 1) return;
    if(pos > heap->size) return;
    
    int left, right, i;
    left = 2 * pos;
    right = 2 * pos + 1;
    
    printHeap(heap, left, level + 1);
    
    for(i = 0; i<level; i++) {
        printf("    ");
    }
    printf("(id: %d, value: %d)\n", pos, heap->element[pos]);
    
    printHeap(heap, right, level + 1);
}

heap_t * makeSampleHeap(int n) {
    heap_t * newHeap = malloc(sizeof(heap_t));
    int * newArray = malloc(sizeof(int) * (n + 1));
    int i;
    
    newHeap->size = n; //배열에 들어있는 node수 - 0번째 자리는 NULL;
    newHeap->capacity = n+1; //배열 사이즈
    newHeap->element = newArray;
    
    newArray[0] = (int) NULL;
    newArray[1] = randMinMax(1, 10);
    for(i = n; i > 1; i--) {
        newArray[i] = n - i + 10;
    }
    
    return newHeap;
}

heap_t * makeSampleHeapManually() {
    heap_t * newHeap = malloc(sizeof(heap_t));
    int * newArray = malloc(sizeof(int) * (5 + 1));
    
    newHeap->size = 5;
    newHeap->capacity = 5+1;
    newHeap->element = newArray;
    
    newArray[0] = (int) NULL;
    newArray[1] = 4;
    newArray[2] = 14;
    newArray[3] = 7;
    newArray[4] = 2;
    newArray[5] = 8;
    
    return newHeap;
}

int randMinMax(int min, int max) {
    return (rand() % max) + min; //[min, max-1+min] 중 리턴
}