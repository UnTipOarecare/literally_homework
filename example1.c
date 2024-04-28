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
    Node **adjacency_list;
} Graph;

Node *create_node(int vertex) {
    Node *new_node = static_cast<Node *>(malloc(sizeof(Node)));
    new_node->vertex = vertex;
    new_node->next = NULL;

    return new_node;
}

void add_edge(Graph *graph, int source, int destination) {
    Node *new_node = create_node(destination);
    new_node->next = graph->adjacency_list[source];
    graph->adjacency_list[source] = new_node;
}

Graph *create_graph(int vertices) {
    Graph *graph = static_cast <Graph*> (malloc(sizeof(Graph)));

    graph->vertices = vertices;
    graph->adjacency_list = static_cast<Node **>(malloc(sizeof(Node *) * vertices));
    graph->visited = static_cast<int *>(malloc(sizeof(int) * vertices));

    for (int i = 0; i < vertices; i++) {
        graph->adjacency_list[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void depth_first_search(Graph *graph, int vertex_number, int destination, int *path_exists) {
    Node *adj_list = graph->adjacency_list[vertex_number];
    Node *aux = adj_list;
    graph->visited[vertex_number] = 1;

    if (vertex_number == destination) {
        *path_exists = 1;
        return;
    }

    while (aux != NULL) {
        int connected_vertex = aux->vertex;
        if (graph->visited[connected_vertex] == 0) {
            depth_first_search(graph, connected_vertex, destination, path_exists);
        }
        aux = aux->next;
    }
}

int main() {
    int num_vertices, num_edges, source, destination;

    printf("Cate noduri are reteaua?\n");
    scanf("%d", &num_vertices);

    printf("Cate muchii are reteaua?\n");
    scanf("%d", &num_edges);

    Graph *graph = create_graph(num_vertices);

    printf("Adauga %d muchii (de la 1 la %d) (exemplu: \"%d 1\"):\n", num_edges, num_vertices, num_vertices);

    for (int i = 0; i < num_edges; i++) {
        int source, destination;
        scanf("%d %d", &source, &destination);
        add_edge(graph, source - 1, destination - 1); // decrementăm pentru a indexa de la 0
    }

    printf("Introduceti sursa si destinatia pentru a verifica existenta unui drum direct:\n");
    scanf("%d %d", &source, &destination);

    int path_exists = 0;

    depth_first_search(graph, source - 1, destination - 1, &path_exists); // decrementăm pentru a indexa de la 0

    if (path_exists) {
        printf("Exista un drum direct intre nodurile %d si %d.\n", source, destination);
    } else {
        printf("Nu exista un drum direct intre nodurile %d si %d.\n", source, destination);
    }

    return 0;
}
