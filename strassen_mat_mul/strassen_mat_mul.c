#include <stdio.h>
#include <stdlib.h>
#define MAX 2

void input(int A[][MAX], int B[][MAX]);
int* multiply(int indices[], int* a, int* b, int s1, int s2);
void print(int*, int size);

int main(int argc, char const *argv[])
{
    int A[MAX][MAX], B[MAX][MAX];

    input(A, B);

    int indices[] = {0, MAX - 1, 0, MAX - 1};
    int* c = multiply(indices, (int*)A, (int*)B, MAX, MAX);

    for (int i = 0; i < MAX; ++i)
    {
        for (int j = 0; j < MAX; ++j)
            printf("%d ", *((c + i * MAX) + j));

        printf("\n");
    }

    free(c);

    return 0;
}

void input(int A[][MAX], int B[][MAX])
{
    printf("Enter matrix A:\n");
    for (int i = 0; i < MAX; ++i)
        for (int j = 0; j < MAX; ++j)
            scanf("%d", &A[i][j]);


    printf("Enter matrix B:\n");
    for (int i = 0; i < MAX; ++i)
        for (int j = 0; j < MAX; ++j)
            scanf("%d", &B[i][j]);
}

void print(int* mat, int size)
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
            printf("%d ", *((mat + i * size) + j));
        printf("\n");
    }
}


int* multiply(int indices[], int* a, int* b, int s1, int s2)
{
    int n = indices[1] - indices[0] + 1;
    int* c = malloc(n  * n * sizeof(int));

    if (n == 1)
    {
        if (s1 != MAX && s2 != MAX)
            *c = *a * *b;
        else if (s2 == MAX)
            *c = *a * *((b + indices[0] * s2) + indices[2]);
        else
            *c = (*((a + indices[0] * s1) + indices[2])) * *b;
    }
    else
    {
        int size = n / 2;

        int a11[] = {indices[0], indices[0] + size - 1, indices[2], indices[2] + size - 1};

        int a12[] = {a11[0], a11[1], a11[3] + 1, indices[3]};

        int a21[] = {a11[1] + 1, indices[1], a11[2], a11[3]};

        int a22[] = {a21[0], a21[1], a21[3] + 1, indices[3]};

        int* mat = malloc(sizeof(int) * size * size);

        for (int i = 0; i < size; ++i)
            for(int j = 0; j < size; ++j)
                *((mat + i * size) + j) = *((b + (i + a12[0]) * s2) + j + a12[2]) - *((b + (i + a22[0]) * s2) + j + a22[2]);

        int* p1 = multiply(a11, a, mat, MAX, size);
        free(mat);

        mat = malloc(sizeof(int) * size * size);

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                *((mat + i * size) + j) = *((a + (i + a11[0]) * s1) + j + a11[2]) + *((a + (i + a12[0]) * s1) + j + a12[2]);


        int* p2 = multiply(a22, mat, b, size, MAX);
        free(mat);

        mat = malloc(sizeof(int) * size * size);

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                *((mat + i * size) + j) = *((a + (i + a21[0]) * s1) + j + a21[2]) + *((a + (i + a22[0]) * s1) + j + a22[2]);


        int* p3 = multiply(a11, mat, b, size, MAX);
        free(mat);

        mat = malloc(sizeof(int) * size * size);

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
            *((mat + i * size) + j) = *((b + (i + a21[0]) * s2) + j + a21[2]) - *((b + (i + a11[0]) * s2) + j + a11[2]);

        int* p4 = multiply(a22, a, mat, MAX, size);
        free(mat);

        int sindices[] = {0, size - 1, 0, size - 1};

        mat = malloc(sizeof(int) * size * size);
        int* mat1 = malloc(sizeof(int) * size * size);

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                *((mat + i * size) + j) = *((a + (i + a11[0]) * s1) + j + a11[2]) + *((a + (i + a22[0]) * s1) + j + a22[2]);

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                *((mat1 + i * size) + j) = *((b + (i + a11[0]) * s2) + j + a11[2]) + *((b + (i + a22[0]) * s2) + j + a22[2]);

        int* p5 = multiply(sindices, mat, mat1, size, size);
        free(mat);
        free(mat1);

        mat = malloc(sizeof(int) * size * size);
        mat1 = malloc(sizeof(int) * size * size);

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                *((mat + i * size) + j) = *((a + (i + a12[0]) * s1) + j + a12[2]) - *((a + (i + a22[0]) * s1) + j + a22[2]);

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                *((mat1 + i * size) + j) = *((b + (i + a21[0]) * s2) + j + a21[2]) + *((b + (i + a22[0]) * s2) + j + a22[2]);

        int* p6 = multiply(sindices, mat, mat1, size, size);
        free(mat);
        free(mat1);

        mat = malloc(sizeof(int) * size * size);
        mat1 = malloc(sizeof(int) * size * size);

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                *((mat + i * size) + j) = *((a + (i + a11[0]) * s1) + j + a11[2]) - *((a + (i + a21[0]) * s1) + j + a21[2]);

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                *((mat1 + i * size) + j) = *((b + (i + a11[0]) * s2) + j + a11[2]) + *((b + (i + a12[0]) * s2) + j + a12[2]);

        int* p7 = multiply(sindices, mat, mat1, size, size);
        free(mat);
        free(mat1);


        for (int i = a11[0], k = 0; i <= a11[1]; ++i, ++k)
            for (int j = a11[2], l = 0; j <= a11[3]; ++j, ++l)
                *((c + i * n) + j) = *((p5 + k * size) + l) + *((p4 + k * size) + l) - *((p2 + k * size) + l) + *((p6 + k * size) + l);

        for (int i = a12[0], k = 0; i <= a12[1]; ++i, ++k)
            for (int j = a12[2], l = 0; j <= a12[3]; ++j, ++l)
                *((c + i * n) + j) = *((p1 + k * size) + l) + *((p2 + k * size) + l);


        for (int i = a21[0], k = 0; i <= a21[1]; ++i, ++k)
            for (int j = a21[2], l = 0; j <= a21[3]; ++j, ++l)
                *((c + i * n) + j) = *((p3 + k * size) + l) + *((p4 + k * size) + l);


        for (int i = a22[0], k = 0; i <= a22[1]; ++i, ++k)
            for (int j = a22[2], l = 0; j <= a22[3]; ++j, ++l)
                *((c + i * n) + j) = *((p5 + k * size) + l) + *((p1 + k * size) + l) - *((p3 + k * size) + l) - *((p7 + k * size) + l);

    }
    return c;
}
