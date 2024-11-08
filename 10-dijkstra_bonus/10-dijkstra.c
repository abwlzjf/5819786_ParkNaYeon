#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10
#define INF 999999

typedef int vertex;

typedef struct DListNode {
    void* data;
    struct DListNode* llink;
    struct DListNode* rlink;
} DListNode;

typedef struct {
    DListNode adj_list[MAX_VERTICES + 1];
    int n;
    int m;
} GraphListType;

typedef struct {
    int v;
    int weight;
} EdgeNode;

typedef struct {
    int* heap;        // 힙 배열
    int* dist;        // 노드에 대한 최소 거리 배열
    int* pos;         // 힙에서 노드의 인덱스를 추적하기 위한 배열
    int size;         // 현재 힙의 크기
    int capacity;     // 힙의 최대 용량
} MinHeap;

void init_Dlist(DListNode* phead) {
    phead->llink = phead;
    phead->rlink = phead;
}

void print_Dlist(DListNode* phead) {
    DListNode* p;
    for (p = phead->rlink; p != phead; p = p->rlink) {
        EdgeNode* edge = (EdgeNode*)p->data;
        printf(" -> |%d (weight %d)|", edge->v, edge->weight);
    }
    printf("\n");
}

void insert_Dlist(DListNode* before, void* data) {
    DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
    newnode->data = data;

    newnode->llink = before;
    newnode->rlink = before->rlink;

    if (before->rlink != NULL) {
        before->rlink->llink = newnode;
    }

    before->rlink = newnode;
}

GraphListType* create_list_graph() {
    return (GraphListType*)malloc(sizeof(GraphListType));
}

void destroy_list_graph(GraphListType* g) {
    for (int i = 0; i <= g->n; i++) {
        DListNode* node = g->adj_list[i].rlink;
        while (node != &(g->adj_list[i])) {
            DListNode* temp = node;
            node = node->rlink;
            free(temp->data);
            free(temp);
        }
    }
    free(g);
}

void init_list_graph(GraphListType* g) {
    for (int i = 0; i < MAX_VERTICES + 1; i++) {
        init_Dlist(&(g->adj_list[i]));
        g->adj_list[i].data = NULL;
    }
    g->n = 0;
    g->m = 0;
}

void insert_vertex_list(GraphListType* g, int v) {
    g->adj_list[v].data = (void*)1;
    g->n++;
}

void insert_edge_list(GraphListType* g, int s, int e, int weight) {
    EdgeNode* edge1 = (EdgeNode*)malloc(sizeof(EdgeNode));
    edge1->v = e;
    edge1->weight = weight;
    insert_Dlist(&(g->adj_list[s]), (void*)edge1);

    EdgeNode* edge2 = (EdgeNode*)malloc(sizeof(EdgeNode));
    edge2->v = s;
    edge2->weight = weight;
    insert_Dlist(&(g->adj_list[e]), (void*)edge2);

    g->m++;
}

void GenerateListGraph(GraphListType* g) {
    insert_vertex_list(g, 1);
    insert_vertex_list(g, 2);
    insert_vertex_list(g, 3);
    insert_vertex_list(g, 4);
    insert_vertex_list(g, 5);
    insert_vertex_list(g, 6);
    insert_vertex_list(g, 7);
    insert_vertex_list(g, 8);
    insert_vertex_list(g, 9);
    insert_vertex_list(g, 10);

    insert_edge_list(g, 1, 2, 3);
    insert_edge_list(g, 1, 6, 11);
    insert_edge_list(g, 1, 7, 12);
    insert_edge_list(g, 2, 3, 5);
    insert_edge_list(g, 2, 4, 4);
    insert_edge_list(g, 2, 5, 1);
    insert_edge_list(g, 2, 6, 7);
    insert_edge_list(g, 2, 7, 8);
    insert_edge_list(g, 3, 4, 2);
    insert_edge_list(g, 3, 7, 6);
    insert_edge_list(g, 3, 8, 5);
    insert_edge_list(g, 4, 5, 13);
    insert_edge_list(g, 4, 8, 14);
    insert_edge_list(g, 4, 10, 16);
    insert_edge_list(g, 5, 6, 9);
    insert_edge_list(g, 5, 9, 18);
    insert_edge_list(g, 5, 10, 17);
    insert_edge_list(g, 7, 8, 13);
    insert_edge_list(g, 8, 10, 15);
    insert_edge_list(g, 9, 10, 10);
}

// MinHeap 관련 함수들

MinHeap* create_min_heap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->capacity = capacity;
    heap->size = 0;
    heap->heap = (int*)malloc((capacity + 1) * sizeof(int));  // 1-based index
    heap->dist = (int*)malloc((capacity + 1) * sizeof(int));  // distance array
    heap->pos = (int*)malloc((capacity + 1) * sizeof(int));   // position tracker
    for (int i = 1; i <= capacity; i++) {
        heap->dist[i] = INF;
        heap->pos[i] = -1;
    }
    return heap;
}

void min_heapify(MinHeap* heap, int i) {
    int smallest = i;
    int left = 2 * i;
    int right = 2 * i + 1;

    if (left <= heap->size && heap->dist[heap->heap[left]] < heap->dist[heap->heap[smallest]]) {
        smallest = left;
    }

    if (right <= heap->size && heap->dist[heap->heap[right]] < heap->dist[heap->heap[smallest]]) {
        smallest = right;
    }

    if (smallest != i) {
        int temp = heap->heap[i];
        heap->heap[i] = heap->heap[smallest];
        heap->heap[smallest] = temp;

        heap->pos[heap->heap[i]] = i;
        heap->pos[heap->heap[smallest]] = smallest;

        min_heapify(heap, smallest);
    }
}

int extract_min(MinHeap* heap) {
    if (heap->size == 0) return -1;

    int root = heap->heap[1];

    heap->heap[1] = heap->heap[heap->size];
    heap->pos[heap->heap[1]] = 1;
    heap->size--;

    min_heapify(heap, 1);

    return root;
}

void decrease_key(MinHeap* heap, int v, int dist) {
    int i = heap->pos[v];
    heap->dist[v] = dist;

    while (i > 1 && heap->dist[heap->heap[i]] < heap->dist[heap->heap[i / 2]]) {
        int temp = heap->heap[i];
        heap->heap[i] = heap->heap[i / 2];
        heap->heap[i / 2] = temp;

        heap->pos[heap->heap[i]] = i;
        heap->pos[heap->heap[i / 2]] = i / 2;

        i = i / 2;
    }
}

// Dijkstra 알고리즘

void dijkstra(GraphListType* g, int start) {
    int dist[MAX_VERTICES + 1];
    int visited[MAX_VERTICES + 1] = { 0 };
    int n = g->n;

    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
    }
    dist[start] = 0;

    MinHeap* heap = create_min_heap(n);
    heap->dist[start] = 0;
    heap->heap[1] = start;
    heap->pos[start] = 1;
    heap->size = 1;

    while (heap->size > 0) {
        int u = extract_min(heap);
        visited[u] = 1;

        DListNode* node = g->adj_list[u].rlink;
        while (node != &(g->adj_list[u])) {
            EdgeNode* edge = (EdgeNode*)node->data;
            int v = edge->v;
            int weight = edge->weight;

            if (!visited[v] && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                decrease_key(heap, v, dist[v]);
            }

            node = node->rlink;
        }
    }

    // 결과 출력
    for (int i = 1; i <= n; i++) {
        printf("Node %d: %d\n", i, dist[i]);
    }

    free(heap->heap);
    free(heap->dist);
    free(heap->pos);
    free(heap);
}

int main() {
    GraphListType* graph = create_list_graph();
    init_list_graph(graph);

    GenerateListGraph(graph);
    dijkstra(graph, 1);

    destroy_list_graph(graph);
    return 0;
}