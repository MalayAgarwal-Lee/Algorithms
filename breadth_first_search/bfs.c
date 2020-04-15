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
    next: node pointer, the next vertex in the lists
*/
struct node
{
    int vertex;
    int distance;
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
Structure for queue
Members:
    array: int array, the queue
    front, read: int, pointers to the front and rear of the queue
A linked list is not used since the queue will simply store integers
*/
typedef struct queue
{
    int* array;
    int front;
    int rear;
}QUEUE;


/*
Structure for the graph
Members:
    vertices: NODE* array, all the vertices in the graph
    adj: LIST* array, the adjacency list for the graph

Pointers and not arrays are used since the graph can have arbitrary number of vertices
*/
typedef struct graph
{
    NODE* vertices;
    LIST* adj;
    int size;
}GRAPH;


// Function prototype to obtain graph details from user and store them in G
void initialize_graph(GRAPH* G);
// Function prototype to print the adjacency list of G
void print_adjlist(GRAPH* G);

// Function prototype of enqueue and dequeue to handle queue operations
void enqueue(QUEUE* q, int i);
int dequeue(QUEUE* q);

// Function prototype to bread-first search graph G starting from vertex s
void bfs(GRAPH* G, int source);


int main(int argc, char const *argv[])
{
    GRAPH G;

    // Initialize the graph
    initialize_graph(&G);
    // Print the adjacency list
    print_adjlist(&G);

    printf("\n");

    int source;

    // Get the source vertex
    printf("Enter the source: ");
    scanf("%d", &source);

    // Call bfs() to start search
    bfs(&G, source);

    return 0;
}


void initialize_graph(GRAPH* G)
{
    /*
    Function to get details from the user about the graph

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
    // The type is NODE* and LIST* since G.vertices and G.adj
    // as they will store NODE and LIST types respectively
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
        // Set distance from source to "infinity"
        v->distance = INT_MAX;
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
        // Only the integer value of the neighbors is stored
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
    printf("The list:\n");
    for (int i = 0; i < G->size; ++i)
    {
        printf("%d\t->", i);

        int size = G->adj[i].size;
        for (int j = 0; j < size; ++j)
            (j < size - 1)? printf("%d->", G->adj[i].neighbors[j]) : printf("%d\\", G->adj[i].neighbors[j]);

        printf("\n");
    }
}


void enqueue(QUEUE* q, int i)
{
    if (q->front == -1 && q->rear == -1)
        q->front = 0;
    q->rear++;
    q->array[q->rear] = i;
}


int dequeue(QUEUE* q)
{
    if (q->front == -1 && q->rear == -1)
        return -1;

    int elem = q->array[q->front];
    q->front++;

    if (q->front > q->rear)
        q->front = q->rear = -1;

    return elem;
}


void bfs(GRAPH* G, int source)
{
    NODE u = G->vertices[source];
    u->color = 'G';
    u->distance = 0;

    int i = u->vertex;

    QUEUE q;
    q.array = malloc(sizeof(int) * G->size);
    q.front = q.rear = -1;

    enqueue(&q, i);

    while ((i = dequeue(&q)) != -1)
    {
        u = G->vertices[i];

        for (int j = 0; j < G->adj[i].size; ++j)
        {
            int neighbor = G->adj[i].neighbors[j];
            NODE v = G->vertices[neighbor];
            if (v->color == 'W')
            {
                v->color = 'G';
                v->distance = u->distance + 1;
                v->predecessor = u;
                enqueue(&q, v->vertex);
            }
        }

        u->color = 'B';
        printf("%d at level %d\n", u->vertex, u->distance);
    }
}





