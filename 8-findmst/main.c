#include <stdio.h>
#include <stdlib.h>
#include "8-findmst.h"

int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);
    GenerateGraph(g);

    QuickKruskal(g);
    MinHeapKruskal(g);

    free(g);
    return 0;
}