#include <stdio.h>
#include <stdlib.h>
#define MAX 2

void input(int A[][MAX], int B[][MAX]);
void create_10_matrices(int a11[], int a12[], int a21[], int a22[], int* s[], int* a, int* b, int s1, int s2);
int* multiply(int indices[], int* a, int* b, int s1, int s2);
void print(int*, int size);

int main(int argc, char const *argv[])
{
    int A[MAX][MAX], B[MAX][MAX];

    input(A, B);
    printf("Calling multiply\n");

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

void create_10_matrices(int a11[], int a12[], int a21[], int a22[], int* s[], int* a, int* b, int s1, int s2)
{
    int part_size = a11[1] - a11[0] + 1;
    printf("Sizes: %d; %d; %d\n", part_size, s1, s2);

    int* mat1 = malloc(sizeof(int) * part_size * part_size);

    for (int i = 0; i < part_size; ++i)
        for(int j = 0; j < part_size; ++j)
            *((mat1 + i * part_size) + j) = *((b + (i + a12[0]) * s2) + j + a12[2]) - *((b + (i + a22[0]) * s2) + j + a22[2]);

    s[0] = mat1;
    printf("Assigned mat1\n");

    int* mat2 = malloc(sizeof(int) * part_size * part_size);

    for (int i = 0; i < part_size; ++i)
        for (int j = 0; j < part_size; ++j)
            *((mat2 + i * part_size) + j) = *((a + (i + a11[0]) * s1) + j + a11[2]) + *((a + (i + a12[0]) * s1) + j + a12[2]);

    s[1] = mat2;
    printf("Assigned mat2\n");


    int* mat3 = (int*)malloc(sizeof(int) * part_size * part_size);

    for (int i = 0; i < part_size; ++i)
        for (int j = 0; j < part_size; ++j)
            *((mat3 + i * part_size) + j) = *((a + (i + a21[0]) * s1) + j + a21[2]) + *((a + (i + a22[0]) * s1) + j + a22[2]);

    s[2] = mat3;
    printf("Assigned mat3\n");

    int* mat4 = (int*)malloc(sizeof(int) * part_size * part_size);

    for (int i = 0; i < part_size; ++i)
        for (int j = 0; j < part_size; ++j)
            *((mat4 + i * part_size) + j) = *((b + (i + a21[0]) * s2) + j + a21[2]) - *((b + (i + a11[0]) * s2) + j + a11[2]);

    s[3] = mat4;
    printf("Assigned mat4\n");

    int* mat5 = (int*)malloc(sizeof(int) * part_size * part_size);

    for (int i = 0; i < part_size; ++i)
        for (int j = 0; j < part_size; ++j)
            *((mat5 + i * part_size) + j) = *((a + (i + a11[0]) * s1) + j + a11[2]) + *((a + (i + a22[0]) * s1) + j + a22[2]);

    s[4] = mat5;
    printf("Assigned mat5\n");

    int* mat6 = (int*)malloc(sizeof(int) * part_size * part_size);

    for (int i = 0; i < part_size; ++i)
        for (int j = 0; j < part_size; ++j)
            *((mat6 + i * part_size) + j) = *((b + (i + a11[0]) * s2) + j + a11[2]) + *((b + (i + a22[0]) * s2) + j + a22[2]);

    s[5] = mat6;
    printf("Assigned mat6\n");

    int* mat7 = (int*)malloc(sizeof(int) * part_size * part_size);

    for (int i = 0; i < part_size; ++i)
        for (int j = 0; j < part_size; ++j)
            *((mat7 + i * part_size) + j) = *((a + (i + a12[0]) * s1) + j + a12[2]) - *((a + (i + a22[0]) * s1) + j + a22[2]);

    s[6] = mat7;
    printf("Assigned mat7\n");

    int* mat8 = (int*)malloc(sizeof(int) * part_size * part_size);

    for (int i = 0; i < part_size; ++i)
        for (int j = 0; j < part_size; ++j)
            *((mat8 + i * part_size) + j) = *((b + (i + a21[0]) * s2) + j + a21[2]) + *((b + (i + a22[0]) * s2) + j + a22[2]);

    s[7] = mat8;
    printf("Assigned mat8\n");

    int* mat9 = (int*)malloc(sizeof(int) * part_size * part_size);

    for (int i = 0; i < part_size; ++i)
        for (int j = 0; j < part_size; ++j)
            *((mat9 + i * part_size) + j) = *((a + (i + a11[0]) * s1) + j + a11[2]) - *((a + (i + a21[0]) * s1) + j + a21[2]);

    s[8] = mat9;
    printf("Assigned mat9\n");

    int* mat10 = (int*)malloc(sizeof(int) * part_size * part_size);

    for (int i = 0; i < part_size; ++i)
        for (int j = 0; j < part_size; ++j)
            *((mat10 + i * part_size) + j) = *((b + (i + a11[0]) * s2) + j + a11[2]) + *((b + (i + a12[0]) * s2) + j + a12[2]);

    s[9] = mat10;
    printf("Assigned mat10\n");
    printf("Exiting 10 matrices.\n");
}

int* multiply(int indices[], int* a, int* b, int s1, int s2)
{
    int n = indices[1] - indices[0] + 1;
    printf("n: %d\n", n);
    int* c = malloc(n  * n * sizeof(int));

    if (n == 1)
        *c = *(a + indices[0] + indices[2]) * *(b + indices[0] + indices[2]);
    else
    {
        printf("Executing else block\n");
        int size = n / 2;

        int a11[] = {indices[0], indices[0] + size - 1, indices[2], indices[2] + size - 1};

        int a12[] = {a11[0], a11[1], a11[3] + 1, indices[3]};

        int a21[] = {a11[1] + 1, indices[1], a11[2], a11[3]};

        int a22[] = {a21[0], a21[1], a21[3] + 1, indices[3]};

        int* s[10];
        printf("About to call 10 matrices\n");
        create_10_matrices(a11, a12, a21, a22, s, a, b, s1, s2);
        printf("Making recursive calls\n");

        int* p1 = multiply(a11, a, s[0], MAX, size);
        int* p2 = multiply(a22, s[1], b, size, MAX);
        int* p3 = multiply(a11, s[2], b, size, MAX);
        int* p4 = multiply(a22, a, s[3], MAX, size);

        int sindices[] = {0, size - 1, 0, size - 1};
        int* p5 = multiply(sindices, s[4], s[5], size, size);
        int* p6 = multiply(sindices, s[6], s[7], size, size);
        int* p7 = multiply(sindices, s[8], s[9], size, size);

        for (int i = 0; i < 10; ++i)
            free(s[i]);

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
