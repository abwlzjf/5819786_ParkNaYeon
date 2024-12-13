#include <stdlib.h>
#include <stdio.h>
#include "17-compareAVL.h"

int compareCount = 0;  // 탐색 중 비교 횟수
int searchCount = 0;   // 탐색 횟수

Node* createNode(int key) {
    Node* nptr = (Node*)malloc(sizeof(Node));
    nptr->key = key;
    nptr->left = nptr->right = NULL;
    nptr->height = 1;
    return nptr;
}

int getHeight(Node* nptr) {
    if (nptr == NULL) return 0;
    return nptr->height;
}

int getBalance(Node* nptr) {
    return getHeight(nptr->left) - getHeight(nptr->right);
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T3 = x->right;

    x->right = y;
    y->left = T3;

    y->height = 1 + ((getHeight(y->left) > getHeight(y->right))
        ? getHeight(y->left)
        : getHeight(y->right));
    x->height = 1 + ((getHeight(x->left) > getHeight(x->right))
        ? getHeight(x->left)
        : getHeight(x->right));

    return x;
}

Node* rotateLeft(Node* y) {
    Node* x = y->right;
    Node* T2 = x->left;

    x->left = y;
    y->right = T2;

    y->height = 1 + ((getHeight(y->left) > getHeight(y->right))
        ? getHeight(y->left)
        : getHeight(y->right));
    x->height = 1 + ((getHeight(x->left) > getHeight(x->right))
        ? getHeight(x->left)
        : getHeight(x->right));

    return x;
}

Node* insertAVL(Node* root, int key) {
    if (root == NULL) return createNode(key);

    // 키 비교 및 삽입
    if (root->key > key) {
        compareCount++;  // 왼쪽 자식으로 삽입
        root->left = insertAVL(root->left, key);
    }
    else if (root->key < key) {
        compareCount++;  // 오른쪽 자식으로 삽입
        root->right = insertAVL(root->right, key);
    }
    else {
        return root;  // 중복된 키는 삽입하지 않음
    }

    // 트리의 높이 업데이트
    root->height = 1 + ((getHeight(root->left) > getHeight(root->right)) 
        ? getHeight(root->left) 
        : getHeight(root->right));

    // 균형 계산
    int balance = getBalance(root);

    // 불균형에 따른 회전 처리
    if (balance > 1 && key < root->left->key)  // LL 회전
        return rotateRight(root);
    if (balance > 1 && key > root->left->key) {  // LR 회전
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && key > root->right->key)  // RR 회전
        return rotateLeft(root);
    if (balance < -1 && key < root->right->key) {  // RL 회전
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

Node* deleteAVL(Node* root, int key) {
    if (root == NULL) return root;

    // 키 비교 및 삭제
    if (key < root->key) {
        compareCount++;  // 왼쪽 자식으로 삭제
        root->left = deleteAVL(root->left, key);
    }
    else if (key > root->key) {
        compareCount++;  // 오른쪽 자식으로 삭제
        root->right = deleteAVL(root->right, key);
    }
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else {
                *root = *temp;
            }
            free(temp);
        }
        else {
            Node* temp = getMinValueNode(root->right);
            root->key = temp->key;
            root->right = deleteAVL(root->right, temp->key);
        }
    }

    if (root == NULL) return root;

    // 트리의 높이 업데이트
    root->height = 1 + ((getHeight(root->left) > getHeight(root->right)) 
        ? getHeight(root->left)
        : getHeight(root->right));

    // 균형 계산
    int balance = getBalance(root);

    // 불균형에 따른 회전 처리
    if (balance > 1 && getBalance(root->left) >= 0)  // LL 회전
        return rotateRight(root);
    if (balance > 1 && getBalance(root->left) < 0) {  // LR 회전
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)  // RR 회전
        return rotateLeft(root);
    if (balance < -1 && getBalance(root->right) > 0) {  // RL 회전
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

Node* getMinValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

Node* searchNode(Node* root, int key) {
    if (root == NULL) return NULL;
    compareCount++;  // 각 비교시마다 증가
    if (root->key == key) {
        return root;
    }
    if (key < root->key) {
        return searchNode(root->left, key);
    }
    return searchNode(root->right, key);
}

Node* insertBinary(Node* root, int key) {
    if (root == NULL) return createNode(key);
    compareCount++;  // 비교시마다 증가

    if (root->key > key) {
        root->left = insertBinary(root->left, key);
    }
    else if (root->key < key) {
        root->right = insertBinary(root->right, key);
    }

    return root;
}

Node* deleteBinary(Node* root, int key) {
    if (root == NULL)return root;
    compareCount++;  // 비교시마다 증가

    if (key < root->key) {
        root->left = deleteBinary(root->left, key);
    }
    else if (key > root->key) {
        root->right = deleteBinary(root->right, key);
    }
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else {
                *root = *temp;
            }
            free(temp);
        }
        else {
            Node* temp = getMinValueNode(root->right);
            root->key = temp->key;
            root->right = deleteBinary(root->right, temp->key);
        }
    }
    return root;
}

void doAVLBatch(Node* root) {
    int operation, key;
    for (int i = 0; i < 2000; i++) {
        operation = rand() % 3;
        key = rand() % 1000;

        if (operation == 0) {
            root = insertAVL(root, key);
        }
        else if (operation == 1) {
            root = deleteAVL(root, key);
        }
        else if (operation == 2) {
            Node* result = searchNode(root, key);
            searchCount++;
        }
    }
}

void doBinaryBatch(Node* root) {
    int operation, key;
    for (int i = 0; i < 2000; i++) {
        operation = rand() % 3;
        key = rand() % 1000;

        if (operation == 0) {
            root = insertBinary(root, key);
        }
        else if (operation == 1) {
            root = deleteBinary(root, key);
        }
        else if (operation == 2) {
            Node* result = searchNode(root, key);
            searchCount++;
        }
    }
}

void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}