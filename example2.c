//parcurgerge  graf cu DFS/BFS

#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Graph {
    int vertices;
    int *visited;
    struct Node **adjacency_lists;
} Graph;

Node *createNode(int vertex) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = vertex;
    new_node->next = NULL;

    return new_node;
}

Graph *create_graph(int vertices) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->adjacency_lists = (Node **)malloc(vertices * sizeof(Node *));
    graph->visited = (int *)malloc(sizeof(int) * vertices);

    int i = 0;
    for (i; i < vertices; i++) {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void addEdge(Graph *graph, int src, int dest) {
    Node *new_node = createNode(dest);

    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = createNode(src);

    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

void insert_edges(int nr_of_vertices, int nr_of_edges, Graph *graph) {
    printf("adauga %d muchii (de la 1 la %d)\n", nr_of_edges, nr_of_vertices);

    int src, dest, i;
    for (i = 0; i < nr_of_edges; i++) {
        scanf("%d%d", &src, &dest);
        addEdge(graph, src, dest);
    }
}

int isEmpty(Node *queue) {
    return queue == NULL;
}

void enqueue(Node **queue, int data) {
    Node *new_node = createNode(data);
    if (isEmpty(*queue))
        *queue = new_node;
    else {
        Node *temp = *queue;
        while (temp->next)
            temp = temp->next;
        temp->next = new_node;
    }
}

int dequeue(Node **queue) {
    int data = (*queue)->data;
    Node *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

void wipeVisitedList(Graph *graph) {
    int i = 0;
    for (i; i < graph->vertices; i++) {
        graph->visited[i] = 0;
    }
}

void depthFirstSearch(Graph *graph, int vertex_number, int *count) {
    if (vertex_number < 0 || vertex_number >= graph->vertices || !graph->adjacency_lists[vertex_number]) {
        return;
    }

    Node *adj_list = graph->adjacency_lists[vertex_number];
    if (!adj_list) {
        return;
    }

    Node *temp = adj_list;

    graph->visited[vertex_number] = 1;
    printf("%d ", vertex_number);

    while (temp != NULL) {
        int connected_vertex = temp->data;

        if (graph->visited[connected_vertex] == 0) {
            (*count)++;
            if (*count == 4) {
                printf("%d ", connected_vertex);
            }
            depthFirstSearch(graph, connected_vertex, count);
        }
        temp = temp->next;
    }
}


void breadthFirstSearch(Graph *graph, int start) {
    Node *queue = NULL;

    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!isEmpty(queue)) {
        int current = dequeue(&queue);
        printf("%d ", current);

        Node *temp = graph->adjacency_lists[current];

        while (temp) {
            int adj_vertex = temp->data;

            if (graph->visited[adj_vertex] == 0) {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}

int main() {
    int nr_of_vertices, nr_of_edges, starting_vertex;

    printf("cate noduri are graful?\n");
    scanf("%d", &nr_of_vertices);

    printf("cate muchii are graful?\n");
    scanf("%d", &nr_of_edges);

    Graph *graph = create_graph(nr_of_vertices);
    insert_edges(nr_of_vertices, nr_of_edges, graph);

    int count = 0; // initialize count variable
    printf("de unde plecam in DFS?\n");
    scanf("%d", &starting_vertex);

    printf("parcurgere cu DFS: ");
    depthFirstSearch(graph, starting_vertex, &count);

    wipeVisitedList(graph);
    printf("\n");

    printf("de unde plecam in BFS?\n");
    scanf("%d", &starting_vertex);

    printf("parcurgere cu BFS: ");
    breadthFirstSearch(graph, starting_vertex);
    printf("\n");

    return 0;
}
