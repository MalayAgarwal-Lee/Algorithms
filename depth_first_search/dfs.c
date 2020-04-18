#include <stdio.h>
#include <stdlib.h>

/*
Structure for a vertex of the graph
Members:
    vertex: int, the vertex as an integer
    discovery: int, the discovery time of the vertex
    finish: int, the finish time of the vertex
    color: char, 'W' for WHITE (unvisited)
                 'B' for BLACK (finish time set/finished)
                 'G' for GRAY (discovery time set/discovered)
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
    time: int, the global timer for discovery and finish times of the vertices
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

// Function prototypes to depth-first search the graph, G
void dfs(GRAPH* G);
void dfs_visit(GRAPH* G, int i);


int main(int argc, char const *argv[])
{
    GRAPH G;

    // Initialize the graph
    initialize_graph(&G);

    // Print the adjacency list
    print_adjlist(&G);

    printf("\n");

    // Call dfs() to start search
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
    /*
    Function which creates the depth-first forest for graph, G
    It finds all vertices which are roots in the trees of the depth-first forest
    And calls dfs_visit() for each root to find all the nodes in that tree

    The DFS algorithm can be looked at here:
    https://en.wikipedia.org/wiki/Depth-first_search

    Parameters:
        G: GRAPH pointer, the graph which needs to be searched

    Returns:
        void
    */

    // Set the global graph timer to 0
    // This will be used to compute the discovery and finish times
    G->time = 0;

    // Loop over the vertices in the graph
    for (int i = 0; i < G->size; ++i)
    {
        // Let u be the current vertex represented by i
        // If u is a node (or root) in another tree of the depth-first forest
        // It cannot be the root of a new tree
        // And will be marked BLACK some previous call to dfs_visit()
        // Hence, only WHITE-colored vertices can be roots
        if (G->vertices[i]->color == 'W')
        {
            // Print the root to demarcate different roots
            printf("Depth-first tree rooted at vertex %d:\n", i);

            // Call dfs_visit() to discover the nodes of the tree rooted at u
            dfs_visit(G, G->vertices[i]->vertex);

            printf("\n");
        }
    }
}


void dfs_visit(GRAPH* G, int i)
{
    /*
    Function which recursively finds all the nodes in the tree rooted at vertex, i
    In the depth-first forest of graph, G
    And computes their discovery and finishing times

    Parameters:
        G: GRAPH pointer, the graph to be searched
        i: int, the root vertex of the tree whose nodes are to be found

    Returns:
        void
    */

    // Get the node represented by i
    NODE u = G->vertices[i];

    // Increment the global graph timer
    // And assign its value to u.discovery
    G->time += 1;
    u->discovery = G->time;

    // Set the color to GRAY to indicate that it has been discovered
    // But all its neighbors haven't been discovered
    u->color = 'G';

    // Loop over the adjacency list of u
    for (int j = 0; j < G->adj[i].size; ++j)
    {
        // Get the vertex stored in the current entry of the adjacency list
        int neighbor = G->adj[i].neighbors[j];
        NODE v = G->vertices[neighbor];

        /*
        In depth-first search, we finish all nodes at the deepest level first
        Then the next deepest level and so on
        So, if u is the  current vertex and the length of the maximum path from u
        To a vertex is x, then this vertex will finish first
        Then vertices at depth x - 1, x - 2 and so on
        Hence, we go "deeper" into the graph by recursively calling dfs_visit()
        WHITE-colored neighbors of u only since non-white vertices have already finished
        Equivalent to finding all the nodes in the subtree rooted at v of the tree rooted at u
        */
        if (v->color == 'W')
        {
            v->predecessor = u;
            dfs_visit(G, v->vertex);
        }
    }

    // Once we have discovered all nodes which are deeper than u, we can finish it
    // Hence, mark color as BLACK
    // Increment global timer and assign to u.finish
    u->color = 'B';
    G->time += 1;
    u->finish = G->time;

    // Print the vertex with its discovery and finish times
    // Due to the nature of DFS, the deepest vertex will be printed first
    // That is, the vertices are printed in increasing order of finishing time
    printf("Vertex %d discovered at %d and finished at %d\n", u->vertex, u->discovery, u->finish);
}
