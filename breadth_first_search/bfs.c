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
    size: int, the number of vertices in the graph
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
        printf("%d\\\n", G->adj[i].neighbors[size - 1])
    }
}


void enqueue(QUEUE* q, int i)
{
    /*
    Function to add the element, i, to the queue, q

    Parameters:
        q: QUEUE pointer, the queue to which the element is to be added
        i: int, the element to be added

    Returns:
        void
    */

    //NOTE: No overflow is checked because that will not occur in this context

    // Check if the queue is empty
    // If it is, then front needs to be set to 0
    // The first index of the array used as queue
    if (q->front == -1 && q->rear == -1)
        q->front = 0;

    // rear can be incremented irrespective of whether queue is empty or not
    q->rear++;

    // Assign i to the new rear of the queue
    q->array[q->rear] = i;
}


int dequeue(QUEUE* q)
{
    /*
    Function to remove the element at the front of the queue

    Parameters:
        q: QUEUE pointer, the queue from which the element is to be removed

    Returns:
        int, the element that was removed
    */

    // If the queue is empty, return -1 indicating underflow
    if (q->front == -1 && q->rear == -1)
        return -1;

    // Get the element to be removed
    int elem = q->array[q->front];

    // Change the front to go to the next index
    // So that size of queue is reduced
    q->front++;

    // If the removal makes the queue empty
    // Set front and rear to -1 to indicate that
    if (q->front > q->rear)
        q->front = q->rear = -1;

    // Return the removed element
    return elem;
}


void bfs(GRAPH* G, int source)
{
    /*
    Function to conduct a breadth-first search on G starting at vertex s

    The BFS algorithm can be looked at here:
    https://en.wikipedia.org/wiki/Breadth-first_search

    Parameters:
        G: GRAPH pointer, the graph that is to be searched
        source: int, the starting vertex
    */

    // Get the source vertex
    // Its color is changed to GRAY to mark that it has been discovered
    // Since this is the source, the distance is 0
    NODE u = G->vertices[source];
    u->color = 'G';
    u->distance = 0;

    // Get the vertex number for the source
    int i = u->vertex;

    // Initialize the queue
    // The queue will store the pending list of all the vertices that have been discovered
    // But whose neighbors are yet to be discovered
    // NOTE: The queue only stores the integer value
    // The actual vertices are only stored in G.vertices
    // And accesses to the vertices need to access G.vertices
    QUEUE q;

    // Allocate memory for the array and initialize the front and the rear
    q.array = malloc(sizeof(int) * G->size);
    q.front = q.rear = -1;

    // Add source vertex to the queue since that is the first to be discovered
    enqueue(&q, i);

    // When the queue is empty, there are no more vertices left to be discovered
    // Or that the search is complete
    while ((i = dequeue(&q)) != -1)
    {
        // Get the actual vertex represented by i from G.vertices
        u = G->vertices[i];

        // Breadth-first search proceeds by first processing all vertices at distance 1 from the source
        // Then distance 2, distance 3 and so on
        // So, if we are at a vertex of distance x
        // We need to first access its neighbors since they will be at distance x + 1 and will be processed next
        for (int j = 0; j < G->adj[i].size; ++j)
        {
            // Get the neighbor's integer value from G.adj
            int neighbor = G->adj[i].neighbors[j];
            // Get the actual vertex using the integer value from G.vertices
            NODE v = G->vertices[neighbor];

            // If the vertex is non-white, it has already been discovered and hence, doesn't need to be processed again
            if (v->color == 'W')
            {
                // Set the color to GRAY to indicate that the neighbor has been discovered
                v->color = 'G';

                // Set the neighbor's distance from source as +1 of the node it was discovered from
                v->distance = u->distance + 1;

                // Set the neighbor's predecessor as the node it was discovered from
                v->predecessor = u;

                // If we were at distance x, this vertex is at distance x + 1.
                // Hence, it should be the one which is processed after all vertices at distance x are processed.
                //Since insertion takes place at the rear of the queue, this behavior is ensured
                enqueue(&q, v->vertex);
            }
        }

        // Set color to BLACK to indicate that all the neighbors have been discovered
        // And added to the queue
        u->color = 'B';

        // Print the node and the level (distance) of the vertex
        // Printing this node is correct since it was discovered first in the search
        printf("%d at level %d\n", u->vertex, u->distance);
    }
}
