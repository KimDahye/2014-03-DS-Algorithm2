//
//  heapSort.c
//  HeapSort
//
//  Created by 김다혜 on 2014. 11. 16..
//  Copyright (c) 2014년 김다혜. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct heap {
    int size;
    int capacity;
    int * element;
} heap_t;

void maxHeapify(heap_t * heap, int pos);
int isMaxHeap(heap_t * heap, int pos);
void buildMaxHeap(heap_t * heap);
void heapSort(heap_t * heap);
int extractMax(heap_t * heap, int * maxValue);
int maxHeapInsert(heap_t * heap, int key);
int increaseHeapSize(heap_t * heap);
void copyArr(int * arr, int size, int * buffer);
heap_t * makeSampleHeap(int n);
int randMinMax(int min, int max);
void printHeap(heap_t * heap, int pos, int level);

int main(int argc, const char * argv[]) {
    //random하게(0개-에러용 1개, 2개, 3개, 4개, 10개) heap 만들고 프린트
    //buildMaxHeap한 다음에 프린트
    //extractMax하고 에러 안난 데에서만 값 확인 후 프린트
    //에러 안 난데에 maxHeapInsert 한 다음에 프린트
    //그다음에 heapsort!
    
    heap_t * heap = NULL;
    int sizes[] = {0,1,2,3,4,10};
    int testCount = sizeof(sizes)/sizeof(int);
    int i, key;
    int * max;
    
    for(i = 0; i < testCount; i++) {
        heap = makeSampleHeap(sizes[i]);
        printf("sample heap:\n");
        printHeap(heap, 1, 0);
        
        buildMaxHeap(heap);
        printf("after buildMaxHeap: \n");
        printHeap(heap, 1, 0);
        
        max = malloc(sizeof(int));
        if(extractMax(heap, max)){
            printf("max value is %d \n", *max);
            printf("after extractMax: \n");
            printHeap(heap, 1, 0);
            
            key = randMinMax(1, 20);
            maxHeapInsert(heap, key);
            printf("after maxHeapInsert(heap, %d): \n", key);
            printHeap(heap, 1, 0);
            
            heapSort(heap);
        }
        printf("-------------------------------------------\n");
        
        free(max);
        free(heap->element);
        free(heap);
    }
    
    //increaseSize에서 copyArr를 쓰도록 maxHeapInsert
    heap = makeSampleHeap(5);
    printf("sample heap:\n");
    printHeap(heap, 1, 0);
    
    buildMaxHeap(heap);
    printf("after buildMaxHeap: \n");
    printHeap(heap, 1, 0);
    
    key = randMinMax(1, 20);
    maxHeapInsert(heap, key);
    printf("after maxHeapInsert(heap, %d): \n", key);
    printHeap(heap, 1, 0);
    
    heapSort(heap);
    
    free(heap->element);
    free(heap);
    return 0;
}

void maxHeapify(heap_t * heap, int pos) {
    //arguments조건: 주어진 heap에서 pos의 subtree들이 모두 maxHeap이어야 한다.
    if(heap == NULL || heap->element == NULL ||heap->size < 1) return;
    if(pos > heap->size) return;
    if(!isMaxHeap(heap, 2*pos) || !isMaxHeap(heap, 2*pos+1)){
        printf("error: given heap is not appropriate\n");
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
    
    if(right <= heap->size && heap->element[right] > heap->element[maxPos]){
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


void buildMaxHeap(heap_t * heap) {
    if(heap == NULL || heap->element == NULL || heap->size < 1) return;
    int i;
    for(i = heap->size/2; i > 0; i--) maxHeapify(heap, i);
}

void heapSort(heap_t * heap) {
    if(heap == NULL || heap->element == NULL || heap->size < 1) return;
    int i, temp;
    buildMaxHeap(heap);
    printf("heapSort: ");
    for(i = heap->size; i > 1; i--) {
        temp = heap->element[1];
        printf("%d, ", temp);
        heap->element[1] = heap->element[i];
        heap->element[i] = temp;
        (heap->size)--;
        maxHeapify(heap, 1);
    }
    printf("%d.\n", heap->element[1]);
}

int extractMax(heap_t * heap, int * maxValue) {
    if(heap == NULL){
        printf("error: given heap does not existed\n");
        return 0;
    }
    if(heap->element == NULL || heap->size < 1) {
        printf("error: heap underflow\n");
        return 0;
    }
    if(!isMaxHeap(heap, 1)){
        printf("error: given heap is not max-heap");
        return 0;
    }
    *(maxValue) = heap->element[1];
    heap->element[1] = heap->element[heap->size];
    (heap->size)--;
    maxHeapify(heap, 1);
    return 1;
}

int maxHeapInsert(heap_t * heap, int key){
    //Insertion이므로 size == 0 이어도 적절한 인자로 취급하겠다.
    if(heap == NULL || heap->element == NULL || heap->size < 0) return 0;
    int i, temp;
    if(!increaseHeapSize(heap)){
        printf("increaseHeapSize error @maxHeapInsert");
        return 0;
    }
    heap->element[heap->size] = key;
    i = heap->size;
    while(i > 1 && heap->element[i/2] < heap->element[i]){
        temp = heap->element[i/2];
        heap->element[i/2] = heap->element[i];
        heap->element[i] = temp;
        i = i/2;
    }
    return 1;
}

int increaseHeapSize(heap_t * heap){
    if(heap == NULL || heap->element == NULL || heap->size < 0) return 0;
    if(heap->size < heap->capacity - 1) {
        heap->size++;
        return 1;
    }
    int * newArr = malloc(sizeof(int)*((heap->capacity)*2));
    copyArr(heap->element, (heap->size)+1, newArr);
    free(heap->element);
    heap->element = newArr;
    (heap->size)++;
    return 1;
    
}

void copyArr(int * arr, int size, int * buffer) {
    if(arr == NULL || size < 1) {
        return;
    }
    int i;
    for(i = 0; i < size; i++){
        buffer[i] = arr[i];
    }
}

heap_t * makeSampleHeap(int n) {
    heap_t * newHeap;
    int * newArray;
    int i;

    newHeap = malloc(sizeof(heap_t));
    if(!newHeap){
        perror("malloc error");
        return NULL;
    }
    newArray = malloc(sizeof(int) * (n + 1));
    if(!newArray){
        perror("malloc error");
        return NULL;
    }
    
    newHeap->size = n; //배열에 들어있는 node수
    newHeap->capacity = n+1; //배열 사이즈 - 0번째 자리는 NULL
    newHeap->element = newArray;
    
    newArray[0] = (int) NULL;
    for(i = 1; i < n + 1; i++) {
        newArray[i] = randMinMax(1, 20);
    }
    
    return newHeap;
}

int randMinMax(int min, int max) {
    return (rand() % max) + min; //[min, max-1+min] 중 리턴
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
