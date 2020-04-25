#include <stdio.h>
#include <stdlib.h>

/*
Structure for a vertex of the graph
Members:
    vertex: int, the vertex as an integer
    color: char, 'W' for WHITE (unplaced)
                 'B' for BLACK (placed)
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
    topological: int* array, the vertices in topological order
    index: int, to index topological
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

// Function prototypes to perform the topological sort
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
        NODE v = (NODE)malloc(sizeof(struct node));
        // Set vertex attribute to i to indicate the vertex number
        v->vertex = i;
        // Set color to WHITE to indicate unvisited
        v->color = 'W';

        // Assign v to G.vertices[i] to store the vertex in the graph
        G->vertices[i] = v;

        // Get the number of neighbors for the vertex
        // And store in G.adj.size for that vertex
        printf("Enter the number of neighbors of vertex %d: ", i);
        scanf("%d", &G->adj[i].size);

        // Don't initialize the adjacency list for this vertex
        // If it does not have any neighbors
        if (G->adj[i].size != 0)
        {
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
        }

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
        for (int j = 0; j < size - 1; ++j)
            printf("%d->", G->adj[i].neighbors[j]);


        // Print last neighbor separately since no "->" is needed after it
        // If the number of neighbors is 0, the above loop will not execute
        // And we don't need to print anything else
        if (size != 0)
            printf("%d\\", G->adj[i].neighbors[size - 1]);

        printf("\n");
    }
}



void topological_sort(GRAPH* G)
{
    /*
    Function which topologically sorts the graph, G
    And prints the vertices of the graph in that order

    The Topological Sort algorithm can be looked at here:
    https://en.wikipedia.org/wiki/Topological_sorting

    ==========================================================================
    In topological sort, if there is an edge in the graph (u, v)
    Then, u must precede v in the sorted order
    This ordering can be correctly found by using the finishing times
    Computed in a DFS
    In DFS, if there is an edge (u, v), then u.finish > v.finish
    If a vertex is added to the front of a list L as soon as it finishes,
    And l[i] = u, l[j] = v, we will have i < j or in other words,
    u will be placed before v in the sort

    Hence, the DFS strategy is followed
    The discovery and finish times are removed since they are irrelevant
    Instead of using a linked list, an integer array is used to store the order
    Since storing the actual vertices is not important

    NOTE: The topological order depends on how the adjacency list is organized
    ==========================================================================

    Parameters:
        G: GRAPH pointer, the graph to be sorted

    Returns:
        void
    */

    // Allocate memory to G.topological
    // To store the vertices in topologically sorted order
    G->topological = (int*)malloc(sizeof(int) * G->size);

    // Vertices are added to the front of the list as they finish
    // In terms of an array, it means we need to start at the end
    // Hence, set G.size to one less than the number of vertices in the graph
    G->index = G->size - 1;

    // Loop over the vertices in the graph
    for (int i = 0; i < G->size; ++i)
    {
        /*
        Let u be the current vertex
        As there is an edge from u to its neighbors
        u will precede all of them in the sorted array
        Since we are starting from the end of the array
        These neighbors need to be placed first, followed by u
        Thus, call topological_sort() on u to discover and place all its neighbors
        If there is an edge from some other vertex x to u
        And x comes before u in the adjacency list
        u must have been marked BLACK by a previous call to topological_visit()
        Thus, only WHITE-colored vertices are considered as they haven't been placed
        */
        if (G->vertices[i]->color == 'W')
            topological_visit(G, G->vertices[i]->vertex);
    }

    // Print the vertices in topologically sorted order
    printf("The vertices of the graph topologically sorted are: ");

    for (int i = 0; i < G->size; ++i)
        printf("%d ", G->topological[i]);

    printf("\n");
}


void topological_visit(GRAPH* G, int i)
{
    /*
    Function which recursively discovers and places all the neighbors of vertex, i
    And then places i in the topologically sorted order

    Parameters:
        G: GRAPH pointer, the graph to be sorted
        i: int, the vertex whose neighbors are to be placed
    */

    // Get the node represented by i
    NODE u = G->vertices[i];

    // Loop over the adjacency list of u
    for (int j = 0; j < G->adj[i].size; ++j)
    {
        // Get the vertex stored in the current entry of the adjacency list
        int neighbor = G->adj[i].neighbors[j];
        NODE v = G->vertices[neighbor];

        /*
        Similar to topological_sort(), since v has edges to all its neighbors
        It will precede them in the topological sort
        Thus, place them before placing v
        This neighbor may have had an incoming edge from some other vertex
        Which came before u in the adjacency list and hence, may have already been placed
        Thus, only WHITE-colored vertices are considered
        */
        if (v->color == 'W')
            topological_visit(G, v->vertex);
    }

    // Once all neighbors of u are placed, we can place u
    // Hence, mark u as BLACK
    u->color = 'B';

    // Add u to G.topological at G.index
    // Previous calls to the function ensure that G.index is the correct index
    G->topological[G->index] = u->vertex;
    // Decrement G.index to point to the next empty space in G.topological
    G->index--;
}
