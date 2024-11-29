#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_NODES 100

// 노드 구조체 정의
typedef struct Node {
    char character;
    int fre;
    struct Node* left;
    struct Node* right;
} Node;

// 우선순위 큐를 위한 노드 구조체
typedef struct MinHeap {
    int size;
    Node* array[MAX_TREE_NODES];
} MinHeap;

// 노드 생성
Node* createNode(char cha, int fre) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->character = cha;
    newNode->fre = fre;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 최소 힙 생성
MinHeap* createMinHeap() {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    return minHeap;
}

// 최소 힙의 현재 상태를 출력
void printMinHeap(MinHeap* minHeap) {
    for (int i = 0; i < minHeap->size; i++) {
        printf("%d ", minHeap->array[i]->fre);
    }
    printf("\n");
}

// 최소 힙에 노드 추가
void insertMinHeap(MinHeap* minHeap, Node* newNode) {
    minHeap->array[minHeap->size++] = newNode;
    int i = minHeap->size - 1;

    // 부모와 비교하여 위치 조정
    while (i && newNode->fre < minHeap->array[(i - 1) / 2]->fre) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = newNode;
}

// 최소 힙에서 최소 노드 제거
Node* extractMin(MinHeap* minHeap) {
    Node* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[--minHeap->size];
    int i = 0;

    // 힙 속성을 유지하기 위해 재정렬
    while (1) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < minHeap->size && minHeap->array[left]->fre < minHeap->array[smallest]->fre) {
            smallest = left;
        }
        if (right < minHeap->size && minHeap->array[right]->fre < minHeap->array[smallest]->fre) {
            smallest = right;
        }
        if (smallest == i) break;

        // 자리를 바꿈
        Node* tempNode = minHeap->array[i];
        minHeap->array[i] = minHeap->array[smallest];
        minHeap->array[smallest] = tempNode;
        i = smallest;
    }
    return temp;
}

// 히프 구조로 허프만 트리 생성
Node* buildHuffmanTree(char characters[], int frequencies[], int size) {
    MinHeap* minHeap = createMinHeap();

    // 각 문자와 빈도로 노드를 생성하여 최소 힙에 추가
    for (int i = 0; i < size; i++) {
        insertMinHeap(minHeap, createNode(characters[i], frequencies[i]));
        // 최소 힙 상태를 출력
        printMinHeap(minHeap);  // 각 노드 추가 후 힙 상태를 출력
    }

    while (minHeap->size > 1) {
        Node* left = extractMin(minHeap);
        Node* right = extractMin(minHeap);

        Node* newNode = createNode('\0', left->fre + right->fre); // 내부 노드
        newNode->left = left;
        newNode->right = right;

        printf("///%d + %d -> %d\n", left->fre, right->fre, newNode->fre);
        insertMinHeap(minHeap, newNode);

        // 합쳐진 후 남은 빈도 수를 출력
        printMinHeap(minHeap);  // 현재 남아 있는 힙 상태 출력
    }

    return extractMin(minHeap);
}

// 허프만 코드를 생성하는 재귀 함수
void generateHuffmanCodes(Node* root, int* code, int top) {
    if (root->left) {
        code[top] = 1; // 왼쪽 자식은 1
        generateHuffmanCodes(root->left, code, top + 1);
    }
    if (root->right) {
        code[top] = 0; // 오른쪽 자식은 0
        generateHuffmanCodes(root->right, code, top + 1);
    }
    if (!root->left && !root->right) { // 리프 노드인 경우
        printf("%c: ", root->character);
        for (int i = 0; i < top; i++) {
            printf("%d", code[i]);
        }
        printf("\n");
    }
}

// 허프만 코드를 생성하는 주요 함수
void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
    Node* root = buildHuffmanTree(characters, frequencies, size);
    int code[MAX_TREE_NODES], top = 0;
    generateHuffmanCodes(root, code, top);
}

int main() {
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int size = sizeof(characters) / sizeof(characters[0]);
    GenerateHuffmanCodes(characters, frequencies, size);
    return 0;
}