#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_VERTICES 5

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
    NODE head;
    NODE tail;
}LINKEDLIST;


typedef struct graph
{
    LINKEDLIST adj[MAX_VERTICES];
}GRAPH;

void initialize_graph(GRAPH* G);
void print_adjlist(GRAPH* G);
void bfs(GRAPH* G, int source);


int main(int argc, char const *argv[])
{
    GRAPH G;

    initialize_graph(&G);
    print_adjlist(&G);

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
        v->next = NULL;
        G->adj[i].head = v;
        G->adj[i].tail = v;

        char neighbor;

        printf("Enter the neighbors of vertex %d separating by space: ", i);
        while((neighbor = getchar()) != '\n')
        {
            if (neighbor != ' ')
            {
                NODE v = (NODE)malloc(sizeof(struct node));
                v->vertex = neighbor - '0';
                v->next = NULL;
                G->adj[i].tail->next = v;
                G->adj[i].tail = v;
            }
        }
    }
}

void print_adjlist(GRAPH* G)
{
    printf("The list:\n");
    for (int i = 0; i < MAX_VERTICES; ++i)
    {
        NODE temp = G->adj[i].head;
        printf("%d->", temp->vertex);

        while ((temp = temp->next) != NULL)
            (temp->next != NULL)? printf("%d->", temp->vertex) : printf("%d\\", temp->vertex);

        printf("\n");
    }
}

void bfs(GRAPH* G, int source)
{

}





