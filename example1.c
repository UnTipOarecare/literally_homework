//Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf
//Graf directionat (dintr-un motiv sau altul)

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vertex;
    struct Node *next;
} Node;

typedef struct Graph {
    int vertices;
    int *visited;
    Node **adjacencyList;
} Graph;

Node *createNode(int vertex) {
    Node *newNode = static_cast<Node *>(malloc(sizeof(Node)));
    newNode->vertex = vertex;
    newNode->next = NULL;

    return newNode;
}

void addEdge(Graph *graph, int source, int destination) {
    Node *newNode = createNode(destination);
    newNode->next = graph->adjacencyList[source];
    graph->adjacencyList[source] = newNode;
}

Graph *createGraph(int vertices) {
    Graph *graph = static_cast <Graph*> (malloc(sizeof(Graph)));

    graph->vertices = vertices;
    graph->adjacencyList = static_cast<Node **>(malloc(sizeof(Node *) * vertices));
    graph->visited = static_cast<int *>(malloc(sizeof(int) * vertices));

    for (int i = 0; i < vertices; i++) {
        graph->adjacencyList[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void depthFirstSearch(Graph *graph, int vertexNumber, int destination, int *pathExists) {
    Node *adjList = graph->adjacencyList[vertexNumber];
    Node *aux = adjList;
    graph->visited[vertexNumber] = 1;

    if (vertexNumber == destination) {
        *pathExists = 1;
        return;
    }

    while (aux != NULL) {
        int connectedVertex = aux->vertex;
        if (graph->visited[connectedVertex] == 0) {
            depthFirstSearch(graph, connectedVertex, destination, pathExists);
        }
        aux = aux->next;
    }
}

int main() {
    int numVertices, numEdges, source, destination;

    printf("Cate noduri are reteaua?\n");
    scanf("%d", &numVertices);

    printf("Cate muchii are reteaua?\n");
    scanf("%d", &numEdges);

    Graph *graph = createGraph(numVertices);

    printf("Adauga %d muchii (de la 1 la %d) (exemplu: \"%d 1\"):\n", numEdges, numVertices, numVertices);

    for (int i = 0; i < numEdges; i++) {
        int source, destination;
        scanf("%d %d", &source, &destination);
        addEdge(graph, source - 1, destination - 1); // decrementăm pentru a indexa de la 0
    }

    printf("Introduceti sursa si destinatia pentru a verifica existenta unui drum direct:\n");
    scanf("%d %d", &source, &destination);

    int pathExists = 0;

    depthFirstSearch(graph, source - 1, destination - 1, &pathExists); // decrementăm pentru a indexa de la 0

    if (pathExists) {
        printf("Exista un drum direct intre nodurile %d si %d.\n", source, destination);
    } else {
        printf("Nu exista un drum direct intre nodurile %d si %d.\n", source, destination);
    }

    return 0;
}
