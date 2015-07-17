//
//  main.c
//  DS2example
//
//  Created by 김다혜 on 2014. 10. 16..
//  Copyright (c) 2014년 김다혜. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node * left;
    struct node * right;
} Node;

Node * createNode();
int countIntNodes(Node * root);
void freeTree(Node * root);
void printArray(int * array, int size);
void insert(int * array, int size);
void insertionSort(int * array, int size);


int main(int argc, const char * argv[]) {
    // insert code here...
    Node * root = createNode(2);
    Node * node1 = createNode(1);
    Node * node3 = createNode(3);
    Node * node4 = createNode(4);
    Node * node5 = createNode(5);
    
    root->left = node1;
    root->right = node3;
    node1->left = node4;
    node4->right = node5;

    //printf("%d, %d\n",countIntNodes(root), countIntNodes(NULL));
    freeTree(root);

    int arr[] = {1,2,3,5,7,4};
    printArray(arr, sizeof(arr)/sizeof(int));
    insert(arr, sizeof(arr)/sizeof(int));
    printArray(arr, sizeof(arr)/sizeof(int));
    
    int arr2[] = {3,6,1,7};
    insertionSort(arr2, sizeof(arr2)/sizeof(int));
    printArray(arr2, sizeof(arr2)/sizeof(int));
    return 0;
}

Node * createNode(int value)
{
    Node * newNode = malloc(sizeof(Node));
    
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    
    return newNode;
}

int countIntNodes(Node * root) {
    if(root == NULL) return 0;
    if(root->left == NULL && root->right == NULL) return 0;
    return 1 + countIntNodes(root->left) + countIntNodes(root->right);
}

void freeTree(Node * root) {
    if(root == NULL) return;
    
    free(root->left);
    free(root->right);
    free(root);
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


