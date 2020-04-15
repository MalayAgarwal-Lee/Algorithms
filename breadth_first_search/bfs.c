#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_VERTICES 8

struct node
{
    int vertex;
    int distance;
    char color;
    struct node* predecessor;
    struct node* next;
};
typedef struct node *NODE;


typedef struct list
{
    int* neighbors;
    int size;
}LIST;


typedef struct queue
{
    int array[MAX_VERTICES];
    int front;
    int rear;
}QUEUE;


typedef struct graph
{
    NODE vertices[MAX_VERTICES];
    LIST adj[MAX_VERTICES];
}GRAPH;


void initialize_graph(GRAPH* G);
void print_adjlist(GRAPH* G);
void enqueue(QUEUE* q, int i);
int dequeue(QUEUE* q);
void bfs(GRAPH* G, int source);


int main(int argc, char const *argv[])
{
    GRAPH G;

    initialize_graph(&G);
    print_adjlist(&G);

    printf("\n");

    int source;

    printf("Enter the source: ");
    scanf("%d", &source);

    bfs(&G, source);

    return 0;
}


void initialize_graph(GRAPH* G)
{
    printf("Please enter details about the graph. Each vertex is represented by an integer. Numbering starts at 0.\n");

    for (int i = 0; i < MAX_VERTICES; ++i)
    {

        NODE v = (NODE)malloc(sizeof(struct node));
        v->vertex = i;
        v->distance = INT_MAX;
        v->color = 'W';
        v->predecessor = NULL;
        v->next = NULL;

        G->vertices[i] = v;

        printf("Enter the number of neighbors of vertex %d: ", i);
        scanf("%d", &G->adj[i].size);

        G->adj[i].neighbors = malloc(sizeof(int) * G->adj[i].size);

        printf("Enter the neighbors of vertex %d separating by space: ", i);
        for (int j = 0; j < G->adj[i].size; ++j)
            scanf("%d", &G->adj[i].neighbors[j]);

        printf("\n");
    }
}


void print_adjlist(GRAPH* G)
{
    printf("The list:\n");
    for (int i = 0; i < MAX_VERTICES; ++i)
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
        q->front = q->rear = 0;
    else
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





