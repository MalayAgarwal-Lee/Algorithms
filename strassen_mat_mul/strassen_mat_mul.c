#include <stdio.h>
#include <stdlib.h>
#define MAX 8


void input(int A[][MAX], int B[][MAX]);
int* multiply(int aindices[], int bindices[], int* a, int* b, int s1, int s2);


int main(int argc, char const *argv[])
{
    int A[MAX][MAX], B[MAX][MAX];

    input(A, B);

    int aindices[] = {0, MAX - 1, 0, MAX - 1};
    int bindices[] = {0, MAX - 1, 0, MAX - 1};
    int* c = multiply(aindices, bindices, (int*)A, (int*)B, MAX, MAX);

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


int* multiply(int aindices[], int bindices[], int* a, int* b, int s1, int s2)
{
    int n = aindices[1] - aindices[0] + 1;
    int* c = malloc(n  * n * sizeof(int));

    if (n == 1)
        *c = *((a + aindices[0] * s1) + aindices[2]) * *((b + bindices[0] * s2) + bindices[2]);
    else
    {
        int size = n / 2;

        int a11[] = {aindices[0], aindices[0] + size - 1, aindices[2], aindices[2] + size - 1};

        int a12[] = {a11[0], a11[1], a11[3] + 1, aindices[3]};

        int a21[] = {a11[1] + 1, aindices[1], a11[2], a11[3]};

        int a22[] = {a21[0], a21[1], a21[3] + 1, aindices[3]};

        int b11[] = {bindices[0], bindices[0] + size - 1, bindices[2], bindices[2] + size - 1};

        int b12[] = {b11[0], b11[1], b11[3] + 1, bindices[3]};

        int b21[] = {b11[1] + 1, bindices[1], b11[2], b11[3]};

        int b22[] = {b21[0], b21[1], b21[3] + 1, bindices[3]};

        int sindices[] = {0, size - 1, 0, size - 1};

        int* mat = malloc(sizeof(int) * size * size);

        for (int i = 0; i < size; ++i)
            for(int j = 0; j < size; ++j)
                *((mat + i * size) + j) = *((b + (i + b12[0]) * s2) + j + b12[2]) - *((b + (i + b22[0]) * s2) + j + b22[2]);


        int* p1 = multiply(a11, sindices, a, mat, s1, size);
        free(mat);

        mat = malloc(sizeof(int) * size * size);

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                *((mat + i * size) + j) = *((a + (i + a11[0]) * s1) + j + a11[2]) + *((a + (i + a12[0]) * s1) + j + a12[2]);


        int* p2 = multiply(sindices, b22, mat, b, size, s2);
        free(mat);

        mat = malloc(sizeof(int) * size * size);

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                *((mat + i * size) + j) = *((a + (i + a21[0]) * s1) + j + a21[2]) + *((a + (i + a22[0]) * s1) + j + a22[2]);


        int* p3 = multiply(sindices, b11, mat, b, size, s2);
        free(mat);

        mat = malloc(sizeof(int) * size * size);

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                *((mat + i * size) + j) = *((b + (i + b21[0]) * s2) + j + b21[2]) - *((b + (i + b11[0]) * s2) + j + b11[2]);

        int* p4 = multiply(a22, sindices, a, mat, s1, size);
        free(mat);

        mat = malloc(sizeof(int) * size * size);
        int* mat1 = malloc(sizeof(int) * size * size);

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                *((mat + i * size) + j) = *((a + (i + a11[0]) * s1) + j + a11[2]) + *((a + (i + a22[0]) * s1) + j + a22[2]);

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                *((mat1 + i * size) + j) = *((b + (i + b11[0]) * s2) + j + b11[2]) + *((b + (i + b22[0]) * s2) + j + b22[2]);

        int* p5 = multiply(sindices, sindices, mat, mat1, size, size);
        free(mat);
        free(mat1);

        mat = malloc(sizeof(int) * size * size);
        mat1 = malloc(sizeof(int) * size * size);

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                *((mat + i * size) + j) = *((a + (i + a12[0]) * s1) + j + a12[2]) - *((a + (i + a22[0]) * s1) + j + a22[2]);

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                *((mat1 + i * size) + j) = *((b + (i + b21[0]) * s2) + j + b21[2]) + *((b + (i + b22[0]) * s2) + j + b22[2]);

        int* p6 = multiply(sindices, sindices, mat, mat1, size, size);
        free(mat);
        free(mat1);

        mat = malloc(sizeof(int) * size * size);
        mat1 = malloc(sizeof(int) * size * size);

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                *((mat + i * size) + j) = *((a + (i + a11[0]) * s1) + j + a11[2]) - *((a + (i + a21[0]) * s1) + j + a21[2]);

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                *((mat1 + i * size) + j) = *((b + (i + b11[0]) * s2) + j + b11[2]) + *((b + (i + b12[0]) * s2) + j + b12[2]);

        int* p7 = multiply(sindices, sindices, mat, mat1, size, size);
        free(mat);
        free(mat1);


        for (int i = 0, k = 0; i < size; ++i, ++k)
            for (int j = 0, l = 0; j < size; ++j, ++l)
                *((c + i * n) + j) = *((p5 + k * size) + l) + *((p4 + k * size) + l) - *((p2 + k * size) + l) + *((p6 + k * size) + l);

        for (int i = 0, k = 0; i < size; ++i, ++k)
            for (int j = n - size, l = 0; j < n; ++j, ++l)
                *((c + i * n) + j) = *((p1 + k * size) + l) + *((p2 + k * size) + l);


        for (int i = n - size, k = 0; i < n; ++i, ++k)
            for (int j = 0, l = 0; j < size; ++j, ++l)
                *((c + i * n) + j) = *((p3 + k * size) + l) + *((p4 + k * size) + l);


        for (int i = n - size, k = 0; i < n; ++i, ++k)
            for (int j = n - size, l = 0; j < n; ++j, ++l)
                *((c + i * n) + j) = *((p5 + k * size) + l) + *((p1 + k * size) + l) - *((p3 + k * size) + l) - *((p7 + k * size) + l);

    }
    return c;
}
