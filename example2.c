//parcurgerge  graf cu DFS/BFS

#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;

typedef struct Graph {
    int vertices;
    int *visited;
    struct Node **adjacencyLists;
} GPH;

NODE *createNode(int vertex) {
    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    newNode->data = vertex;
    newNode->next = NULL;

    return newNode;
}

GPH *createGraph(int vertices) {
    GPH *graph = (GPH *)malloc(sizeof(GPH));
    graph->vertices = vertices;
    graph->adjacencyLists = (Node **)malloc(vertices * sizeof(NODE *));
    graph->visited = (int *)malloc(sizeof(int) * vertices);

    int i = 0;
    for (i; i < vertices; i++) {
        graph->adjacencyLists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void addEdge(GPH *graph, int src, int dest) {
    NODE *newNode = createNode(dest);

    newNode->next = graph->adjacencyLists[src];
    graph->adjacencyLists[src] = newNode;

    newNode = createNode(src);

    newNode->next = graph->adjacencyLists[dest];
    graph->adjacencyLists[dest] = newNode;
}

void insedg(int nrOfVertices, int nrOfEdges, GPH *graph) {
    printf("adauga %d muchii (de la 1 la %d)\n", nrOfEdges, nrOfVertices);

    int src, dest, i;
    for (i = 0; i < nrOfEdges; i++) {
        scanf("%d%d", &src, &dest);
        addEdge(graph, src, dest);
    }
}

int isEmpty(NODE *queue) {
    return queue == NULL;
}

void enqueue(NODE **queue, int data) {
    NODE *newNode = createNode(data);
    if (isEmpty(*queue))
        *queue = newNode;
    else {
        NODE *temp = *queue;
        while (temp->next)
            temp = temp->next;
        temp->next = newNode;
    }
}

int dequeue(NODE **queue) {
    int data = (*queue)->data;
    NODE *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}


void printGraph(GPH *graph) {
    int i;
    for (i = 0; i < graph->vertices; i++) {
        printf("Adjacency list of vertex %d: ", i);
        NODE *temp = graph->adjacencyLists[i];
        while (temp) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

void printQueue(NODE *queue) {
    while (queue != NULL) {
        printf("%d ", queue->data);
        queue = queue->next;
    }
}

void wipeVisitedList(GPH *graph) {
    int i = 0;
    for (i; i < graph->vertices; i++) {
        graph->visited[i] = 0;
    }
}

void DFS(GPH *graph, int vertexNumber, int *count) {
    if (vertexNumber < 0 || vertexNumber >= graph->vertices || !graph->adjacencyLists[vertexNumber]) {
        return;
    }

    NODE *adjList = graph->adjacencyLists[vertexNumber];
    if (!adjList) {
        return;
    }

    NODE *temp = adjList;

    graph->visited[vertexNumber] = 1;
    printf("%d ", vertexNumber);

    while (temp != NULL) {
        int connectedVertex = temp->data;

        if (graph->visited[connectedVertex] == 0) {
            (*count)++;
            if (*count == 4) {
                printf("%d ", connectedVertex);
            }
            DFS(graph, connectedVertex, count);
        }
        temp = temp->next;
    }
}


void BFS(GPH *graph, int start) {
    NODE *queue = NULL;

    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!isEmpty(queue)) {
        int current = dequeue(&queue);
        printf("%d ", current);

        NODE *temp = graph->adjacencyLists[current];

        while (temp) {
            int adjVertex = temp->data;

            if (graph->visited[adjVertex] == 0) {
                graph->visited[adjVertex] = 1;
                enqueue(&queue, adjVertex);
            }
            temp = temp->next;
        }
    }
}

int main() {
    int nrOfVertices, nrOfEdges, startingVertex;

    printf("cate noduri are graful?\n");
    scanf("%d", &nrOfVertices);

    printf("cate muchii are graful?\n");
    scanf("%d", &nrOfEdges);

    GPH *graph = createGraph(nrOfVertices);
    insedg(nrOfVertices, nrOfEdges, graph);

    int count = 0; // initialize count variable
    printf("de unde plecam in DFS?\n");
    scanf("%d", &startingVertex);

    printf("parcurgere cu DFS: ");
    DFS(graph, startingVertex, &count);

    wipeVisitedList(graph);
    printf("\n");

    printf("de unde plecam in BFS?\n");
    scanf("%d", &startingVertex);

    printf("parcurgere cu BFS: ");
    BFS(graph, startingVertex);
    printf("\n");

    return 0;
}
