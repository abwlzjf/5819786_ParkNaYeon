#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 50

typedef struct GraphType {
    int n;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

GraphType* create_graph() {
    return (GraphType*)malloc(sizeof(GraphType));
}

void init_graph(GraphType* g) {
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++)
        for (int j = 0; j < MAX_VERTICES; j++)
            g->adj_mat[i][j] = 0;
}

void insert_vertex(GraphType* g, int v) {
    if ((g->n + 1) > MAX_VERTICES) {
        fprintf(stderr, "Over number of vertex\n");
        return;
    }
    (g->n)++;
}

void insert_edge(GraphType* g, int s, int e) {
    if (s >= g->n || e >= g->n) {
        fprintf(stderr, "Vertex number error\n");
        return;
    }
    g->adj_mat[s][e] = 1;
    g->adj_mat[e][s] = 1;
}

// ���� �켱 Ž��
void dfs(GraphType* g, int start, int target) {
    int visited[MAX_VERTICES] = { 0 };
    int stack[MAX_VERTICES], top = -1;
    int visit_count = 0;

    stack[++top] = start;
    visited[start] = 1;  // ������
    printf("%d ", start);

    while (top != -1) {
        int v = stack[top--];
        visit_count++;

        if (v == target) {
            printf("\nŽ�� ����: %d\n", target);
            printf("�湮�� ����� ��: %d\n", visit_count);
            return;
        }

        // ���� ��� Ž��
        int backtrack = 1;
        for (int i = 0; i < g->n; i++) {
            if (g->adj_mat[v][i] && !visited[i]) {
                stack[++top] = v;  // ��Ʈ��ŷ
                stack[++top] = i; 
                visited[i] = 1;
                printf("%d ", i);
                backtrack = 0;
                break;
            }
        }

        if (backtrack && top != -1) {
            printf("%d ", stack[top]);
        }
    }
    // Ž�� ����
    printf("\nŽ�� ����: %d\n", target);
    printf("�湮�� ����� ��: %d\n", visit_count);
}

void bfs(GraphType* g, int start, int target) {
    int visited[MAX_VERTICES] = { 0 };
    int queue[MAX_VERTICES], front = 0, rear = 0;
    int visit_count = 0;

    queue[rear++] = start;
    visited[start] = 1;
    printf("%d ", start);

    while (front != rear) {
        int v = queue[front++];
        visit_count++;

        if (v == target) {
            printf("\nŽ�� ����: %d\n", target);
            printf("�湮�� ����� ��: %d\n", visit_count);
            return;
        }

        // ���� ��� Ž��
        for (int i = 0; i < g->n; i++) {
            if (g->adj_mat[v][i] && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1; 
                printf("%d ", i);
            }
        }
    }
    
    printf("\nŽ�� ����: %d\n", target);
    printf("�湮�� ����� ��: %d\n", visit_count);
}

void runUserInterface(GraphType* g) {
    int choice, s, e;

    printf("�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�\n");
    printf(" 1\t: ���� �켱 Ž�� \t��\n");
    printf(" 2\t: �ʺ� �켱 Ž�� \t��\n");
    printf(" 3\t: ����    \t\t��\n");
    printf("�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�\n\n");

    while (1) {
        printf("\n");
        printf("�޴��Է�: ");
        scanf_s("%d", &choice);
        switch (choice) {
        case 1:
            printf("���� ��ȣ�� Ž���� �� �Է�: ");
            scanf_s("%d %d", &s, &e);
            dfs(g, s, e);
            break;
        case 2:
            printf("���� ��ȣ�� Ž���� �� �Է�: ");
            scanf_s("%d %d", &s, &e);
            bfs(g, s, e);
            break;
        case 3:
            printf("���α׷� ����\n");
            exit(0);
            break;
        default:
            printf("�ٽ� �Է�.\n");
            break;
        }
    }
}

int main() {
    GraphType* g;
    g = create_graph();
    init_graph(g);
    for (int i = 0; i < 11; i++) {
        insert_vertex(g, i);
    }

    insert_edge(g, 0, 2);
    insert_edge(g, 0, 4);
    insert_edge(g, 0, 5);
    insert_edge(g, 0, 6);
    insert_edge(g, 0, 9);
    insert_edge(g, 1, 4);
    insert_edge(g, 1, 5);
    insert_edge(g, 1, 7);
    insert_edge(g, 1, 10);
    insert_edge(g, 2, 3);
    insert_edge(g, 2, 4);
    insert_edge(g, 3, 4);
    insert_edge(g, 3, 5);
    insert_edge(g, 4, 5);
    insert_edge(g, 4, 6);
    insert_edge(g, 4, 7);
    insert_edge(g, 6, 7);
    insert_edge(g, 6, 8);
    insert_edge(g, 7, 10);
    insert_edge(g, 8, 9);
    insert_edge(g, 8, 10);

    runUserInterface(g);

    free(g);
    return 0;
}