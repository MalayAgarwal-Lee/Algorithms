#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*
Structure for a vertex of the graph
Members:
    vertex: int, the vertex as an integer
    distance: int, the distance from source to the vertex
    color: char, 'W' for WHITE (unvisited)
                 'B' for BLACK (all neighbors visited)
                 'G' for GRAY (discovered/visited)
    predecessor: node pointer, the predecessor of the vertex
*/
struct node
{
    int vertex;
    int discovery;
    int finish;
    char color;
    struct node* predecessor;
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
    int size;
    int time;
}GRAPH;


// Function prototype to obtain graph details from user and store them in G
void initialize_graph(GRAPH* G);
// Function prototype to print the adjacency list of G
void print_adjlist(GRAPH* G);

void dfs(GRAPH* G);
void dfs_visit(GRAPH* G, int i);


int main(int argc, char const *argv[])
{
    GRAPH G;

    initialize_graph(&G);

    print_adjlist(&G);

    printf("\n");

    dfs(&G);

    return 0;
}


void initialize_graph(GRAPH* G)
{
    /*
    Function to get details from the user about the graph, G

    Parameters:
        G: GRAPH pointer, the graph to be initialized

    Returns:
        void
    */

    // Get the size of the graph and store in G.size
    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &G->size);

    // Allocate memory to G.vertices and G.adj arrays to store the
    // vertices and the adjacency list respectively
    // The type is NODE* and LIST*
    // As they will store NODE and LIST types respectively
    G->vertices = (NODE*)malloc(sizeof(struct node) * G->size);
    G->adj = (LIST*)malloc(sizeof(struct list) * G->size);

    printf("Please enter details about the graph. Each vertex is represented by an integer. Numbering starts at 0.\n");

    // Get details about the vertices and their neighbors
    // To initialize G.vertices and G.adj
    for (int i = 0; i < G->size; ++i)
    {
        // Allocate memory to a new node
        NODE v = (NODE)malloc(sizeof(struct node));
        // Set vertex attribute to i to indicate the vertex number
        v->vertex = i;
        // Set color to WHITE to indicate unvisited
        v->color = 'W';
        // Set predecessor to NULL to indicate no predecessor
        v->predecessor = NULL;

        // Assign v to G.vertices[i] to store the vertex in the graph
        G->vertices[i] = v;

        // Get the number of neighbors for the vertex
        // And store in G.adj.size for that vertex
        printf("Enter the number of neighbors of vertex %d: ", i);
        scanf("%d", &G->adj[i].size);

        // Allocate memory for array to store the neighbors
        // NOTE: The adjacency list stores only the integer value of the neighbors
        // The actual vertices are only stored in G.vertices
        // And accesses to the vertices need to access G.vertices
        G->adj[i].neighbors = malloc(sizeof(int) * G->adj[i].size);

        // Get integer value of all the neighbors of the vertex
        // And store in G.adj.neighbors for that vertex
        printf("Enter the neighbors of vertex %d separating by space: ", i);
        for (int j = 0; j < G->adj[i].size; ++j)
            scanf("%d", &G->adj[i].neighbors[j]);

        printf("\n");
    }
}


void print_adjlist(GRAPH* G)
{
    /*
    Function to print the adjacency list of graph, G

    Parameters:
        G: GRAPH pointer, the graph whose adjacency list needs to be printed

    Output format:
    0   ->1->4\
    1   ->0->4->2->3\

    Returns:
        void
    */

    printf("The list:\n");
    for (int i = 0; i < G->size; ++i)
    {
        printf("%d\t->", i);

        // Get the number of neighbors for the vertex
        int size = G->adj[i].size;
        // Print each neighbor except the last one
        for (int j = 0; j < size - 1; ++j)
            printf("%d->", G->adj[i].neighbors[j]);

        // Print last neighbor separately since no "->" is needed after it
        printf("%d\\\n", G->adj[i].neighbors[size - 1]);
    }
}


void dfs(GRAPH* G)
{
    G->time = 0;

    for (int i = 0; i < G->size; ++i)
    {
        if (G->vertices[i]->color == 'W')
        {
            printf("Depth-first tree rooted at vertex %d:\n", i);
            dfs_visit(G, G->vertices[i]->vertex);
            printf("\n");
        }
    }
}


void dfs_visit(GRAPH* G, int i)
{
    NODE u = G->vertices[i];

    G->time += 1;

    u->discovery = G->time;
    u->color = 'G';

    for (int j = 0; j < G->adj[i].size; ++j)
    {
        int neighbor = G->adj[i].neighbors[j];
        NODE v = G->vertices[neighbor];

        if (v->color == 'W')
        {
            v->predecessor = u;
            dfs_visit(G, v->vertex);
        }
    }

    u->color = 'B';
    G->time += 1;
    u->finish = G->time;

    printf("Vertex %d discovered at %d and finished at %d\n", u->vertex, u->discovery, u->finish);
}
