#include <stdio.h>
#include <stdlib.h>

/*
Structure for a vertex of the graph
Members:
    vertex: int, the vertex as an integer
    color: char, 'W' for WHITE (unvisited)
                 'B' for BLACK (visited)
*/
struct node
{
    int vertex;
    char color;
};

// Alias for creating pointer of the above structure
typedef struct node *NODE;


/*
Structure for the list of neighbors for a vertex
Members:
    neighbors: int pointer, array to store all the neighbors
    size: int, the number of neighbors of the vertex
*/
typedef struct list
{
    int* neighbors;
    int size;
}LIST;


/*
Structure for the graph
Members:
    vertices: NODE* array, all the vertices in the graph
    adj: LIST* array, the adjacency list for the graph
    size: int, the number of vertices in the graph
Pointers and not arrays are used since the graph can have arbitrary number of vertices
*/
typedef struct graph
{
    NODE* vertices;
    LIST* adj;
    int* topological;
    int index;
    int size;
}GRAPH;


// Function prototype to obtain graph details from user and store them in G
void initialize_graph(GRAPH* G);
// Function prototype to print the adjacency list of G
void print_adjlist(GRAPH* G);

// Function prototypes to depth-first search the graph, G
void topological_sort(GRAPH* G);
void topological_visit(GRAPH* G, int i);


int main(int argc, char const *argv[])
{
    GRAPH G;

    // Initialize the graph
    initialize_graph(&G);

    // Print the adjacency list
    print_adjlist(&G);

    printf("\n");

    topological_sort(&G);

    return 0;
}


void initialize_graph(GRAPH* G)
{

    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &G->size);

    G->vertices = (NODE*)malloc(sizeof(struct node) * G->size);
    G->adj = (LIST*)malloc(sizeof(struct list) * G->size);

    G->topological = (int*)malloc(sizeof(int) * G->size);
    G->index = G->size - 1;

    printf("Please enter details about the graph. Each vertex is represented by an integer. Numbering starts at 0.\n");

    for (int i = 0; i < G->size; ++i)
    {
        NODE v = (NODE)malloc(sizeof(struct node));
        v->vertex = i;
        v->color = 'W';

        G->vertices[i] = v;

        printf("Enter the number of neighbors of vertex %d: ", i);
        scanf("%d", &G->adj[i].size);

        if (G->adj[i].size != 0)
        {

            G->adj[i].neighbors = malloc(sizeof(int) * G->adj[i].size);

            printf("Enter the neighbors of vertex %d separating by space: ", i);
            for (int j = 0; j < G->adj[i].size; ++j)
                scanf("%d", &G->adj[i].neighbors[j]);
        }

        printf("\n");
    }
}


void print_adjlist(GRAPH* G)
{

    printf("The list:\n");
    for (int i = 0; i < G->size; ++i)
    {
        printf("%d\t->", i);

        int size = G->adj[i].size;
        for (int j = 0; j < size - 1; ++j)
            printf("%d->", G->adj[i].neighbors[j]);

        if (size != 0)
            printf("%d\\", G->adj[i].neighbors[size - 1]);

        printf("\n");
    }
}



void topological_sort(GRAPH* G)
{
    for (int i = 0; i < G->size; ++i)
    {
        if (G->vertices[i]->color == 'W')
            topological_visit(G, G->vertices[i]->vertex);
    }

    printf("The vertices of the graph topologically sorted are: ");

    for (int i = 0; i < G->size; ++i)
        printf("%d ", G->topological[i]);

    printf("\n");
}


void topological_visit(GRAPH* G, int i)
{

    NODE u = G->vertices[i];

    for (int j = 0; j < G->adj[i].size; ++j)
    {
        int neighbor = G->adj[i].neighbors[j];
        NODE v = G->vertices[neighbor];

        if (v->color == 'W')
            topological_visit(G, v->vertex);
    }

    u->color = 'B';

    G->topological[G->index] = u->vertex;
    G->index--;
}
