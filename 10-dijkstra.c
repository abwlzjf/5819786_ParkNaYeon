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

void print_distances(int* dist, int n) {
    printf("Distance:");
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INF) printf(" *");
        else printf(" %d", dist[i]);
    }
    printf("\n");
}

void print_found(int* found, int n) {
    printf("Found:");
    for (int i = 1; i <= n; i++) {
        printf(" %d", found[i]);
    }
    printf("\n\n");
}

void dijkstra(GraphListType* g, int start) {
    int dist[MAX_VERTICES + 1];
    int visited[MAX_VERTICES + 1] = { 0 };
    int found_order[MAX_VERTICES + 1];
    int found_count = 0;

    int n = g->n;
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
    }
    dist[start] = 0;

    for (int i = 0; i < n; i++) {
        int minDist = INF;
        int u = -1;
        for (int v = 1; v <= n; v++) {
            if (!visited[v] && dist[v] < minDist) {
                minDist = dist[v];
                u = v;
            }
        }

        if (u == -1) break;

        visited[u] = 1;
        found_order[found_count++] = u;

        print_distances(dist, n);
        print_found(visited, n);

        DListNode* node = g->adj_list[u].rlink;
        while (node != &(g->adj_list[u])) {
            EdgeNode* edge = (EdgeNode*)node->data;
            int v = edge->v;
            int weight = edge->weight;
            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
            node = node->rlink;
        }
    }

    printf("Found Order: ");
    for (int i = 0; i < found_count; i++) {
        printf("%d ", found_order[i]);
    }
    printf("\n");
}

int main() {
    GraphListType* graph = create_list_graph();
    init_list_graph(graph);

    GenerateListGraph(graph);
    dijkstra(graph, 1);

    destroy_list_graph(graph);
    return 0;
}