#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define INF 999999
#define NUM_VERTICES 10

typedef struct {
    int key;    // 가중치
    int vertex; // 연결된 정점 번호
} element;

typedef struct {
    element heap[MAX_SIZE];
    int heap_size;
} HeapType;

typedef struct GraphListNode {
    int vertex;
    int weight;
    struct GraphListNode* next;
} GraphListNode;

HeapType* create_heap() {
    return (HeapType*)malloc(sizeof(HeapType));
}

void init_heap(HeapType* h) {
    h->heap_size = 0;
}

void destroy_heap(HeapType* h) {
    free(h);
}

int is_empty_heap(HeapType* h) {
    return (h->heap_size == 0);
}

void insert_min_heap(HeapType* h, element item) {
    int i = ++(h->heap_size);
    while (i != 1 && item.key < h->heap[i / 2].key) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

element delete_min_heap(HeapType* h) {
    int parent, child;
    element item, temp;

    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];

    parent = 1;
    child = 2;

    while (child <= h->heap_size) {
        if (child < h->heap_size && h->heap[child].key > h->heap[child + 1].key)
            child++;
        if (temp.key <= h->heap[child].key)
            break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}
GraphListNode* adj[NUM_VERTICES + 1];
int distance[NUM_VERTICES + 1];
int found[NUM_VERTICES + 1];
int found_order[NUM_VERTICES];
int order_index = 0;// found_order인덱스

void insert_edge(int u, int v, int weight) {
    GraphListNode* new_node = (GraphListNode*)malloc(sizeof(GraphListNode));
    new_node->vertex = v;
    new_node->weight = weight;
    new_node->next = adj[u];
    adj[u] = new_node;
}

void dijkstra(int start) {
    HeapType* heap = create_heap();
    init_heap(heap);

    // 시작정점 초기화
    for (int i = 1; i <= NUM_VERTICES; i++) {
        distance[i] = INF;
        found[i] = 0;
    }
    distance[start] = 0;
    insert_min_heap(heap, (element) { 0, start });

    while (!is_empty_heap(heap)) {
        element min_elem = delete_min_heap(heap);
        int u = min_elem.vertex;

        // 이미 최단 경로에 포함된 경우 무시
        if (found[u]) continue;

        found[u] = 1;
        found_order[order_index++] = u;

        printf("Distance: ");
        for (int i = 1; i <= NUM_VERTICES; i++) {
            if (distance[i] == INF)
                printf("* ");
            else
                printf("%d ", distance[i]);
        }
        printf("\nFound: ");
        for (int i = 1; i <= NUM_VERTICES; i++) {
            printf("%d ", found[i]);
        }
        printf("\n\n");

        for (GraphListNode* node = adj[u]; node != NULL; node = node->next) {
            int v = node->vertex;
            int weight = node->weight;

            if (!found[v] && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                insert_min_heap(heap, (element) { distance[v], v });
            }
        }
    }
    printf("Found Order: ");
    for (int i = 0; i < order_index; i++) {
        printf("%d ", found_order[i]);
    }
    printf("\n");

    destroy_heap(heap);
}

int main() {
    insert_edge(1, 2, 3);
    insert_edge(1, 7, 12);
    insert_edge(1, 6, 11);
    insert_edge(2, 3, 5);
    insert_edge(2, 4, 4);
    insert_edge(2, 5, 1);
    insert_edge(2, 6, 7);
    insert_edge(2, 7, 8);
    insert_edge(3, 4, 2);
    insert_edge(3, 7, 6);
    insert_edge(3, 8, 5);
    insert_edge(4, 5, 13);
    insert_edge(4, 8, 14);
    insert_edge(4, 10, 16);
    insert_edge(5, 6, 9);
    insert_edge(5, 9, 18);
    insert_edge(5, 10, 17);
    insert_edge(7, 8, 13);
    insert_edge(8, 10, 15);
    insert_edge(9, 10, 10);

    dijkstra(1);

    return 0;
}