#pragma once

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

extern int compareCount;
extern int searchCount;
extern void freeTree(Node* root);
extern void doAVLBatch(Node* root);
extern void doBinaryBatch(Node* root);