#include <stdio.h>
#define MAT_COUNT 10

int* optimal_parenthesize(int dimensions[], int m[][MAT_COUNT + 1], int i, int j);
int print_optimal_parenthesization(int s[][], int, int);

int main(int argc, char const *argv[])
{
    int dimensions[MAT_COUNT + 1];
    int m[MAT_COUNT + 1][MAT_COUNT + 1], s[][];

    printf("Enter the dimensions of the matrices as an array (p0 p1 ... pn): ");
    for (int i = 0; i < MAT_COUNT; ++i)
        scanf("%d", &dimensions[i]);



    return 0;
}



