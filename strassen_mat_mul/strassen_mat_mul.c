#include <stdio.h>
#include <stdlib.h>
#define MAX 4

// Function prototype to take input from the user
void input(int A[][MAX], int B[][MAX]);
// Function prototype which multiplies 'a' and 'b' and returns their product
int* multiply(int aindices[], int bindices[], int* a, int* b, int s1, int s2);


int main(int argc, char const *argv[])
{
    int A[MAX][MAX], B[MAX][MAX];

    // Getting the matrices
    input(A, B);

    // Defining the initial values of aindices and bindices
    // Intuitively implies that we need to consider the entire matrix for the first call
    int aindices[] = {0, MAX - 1, 0, MAX - 1};
    int bindices[] = {0, MAX - 1, 0, MAX - 1};

    // Making the first call to multiply() to begin recursion
    // The 2D arrays A and B are converted to int* to facilitate in-place partitioning of A and B
    int* c = multiply(aindices, bindices, (int*)A, (int*)B, MAX, MAX);

    // Displaying the result
    for (int i = 0; i < MAX; ++i)
    {
        for (int j = 0; j < MAX; ++j)
            printf("%d ", *((c + i * MAX) + j));

        printf("\n");
    }

    // In each call to multiply(), c is dynamically allocated
    // That memory is freed in the end
    free(c);

    return 0;
}


// Function definition of input()
// A simple loop on each (i, j) pairs
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


// Function definition of multiply
int* multiply(int aindices[], int bindices[], int* a, int* b, int s1, int s2)
{

    /*
    Function which multiplies two matrices a and b of sizes s1 and s2 respectively recursively
    Note: The sizes of the matrices needs to be a power of 2

    Parameters:
        aindices: int array, range of indices representing the partition to be considered for this recursive call in a
        bindices: int array, range of indices representing the partition to be considered for this recursive call in b
        a: int pointer, a pointer to the 'A' matrix in A.B
        b: int pointer, a pointer to the 'B' matrix in A.B
        s1: Size of A in A.B
        s2: Size of B in A.B

    Format of aindices, bindices: {start_row, end_row, start_col, end_col} (0-indexed)

    Return value:
        c: int pointer, a pointer to the result of A.B
    */

    // Calculating the matrix size
    // Note: s1 and s2 may or may not be equal to n
    // Since partitioning is done in-place (instead of copying into new matrices)
    int n = aindices[1] - aindices[0] + 1;

    // Allocating required amount of space for the result of multiplication
    int* c = malloc(n  * n * sizeof(int));

    if (n == 1)
        // If n == 1, c will have only one element and the value will be a product of two elements of A and B
        // Due to in-place partition, a and b may refer to the original matrices
        // Or to a matrix created by this function in a previous recursive call
        // Therefore, instead of simply doing *a * *b
        // The value is scaled by the size according to the partitions that are to be considered
        *c = *((a + aindices[0] * s1) + aindices[2]) * *((b + bindices[0] * s2) + bindices[2]);
    else
    {
        // If n > 1, we need to partition the matrices into 4 matrices, A11, A12, A21, A22 and similarly for B
        // Where the size of each partition is n/2
        int size = n / 2;

        // Partitioning can be done by copying entries into new matrices
        // But it can be done in-place by specifying a range of indices - Former is O(n ^ 2) and this is O(1)
        // Indices of the new partitions need to be calculated in terms of indices of previous (n X n) partitions
        // This ensures that we have the correct indices in terms of the original matrices (A and B)

        // A11 will start at row and column where the previous partition started
        // The end row and column will be n/2 more than the respective starts
        int a11[] = {aindices[0], aindices[0] + size - 1, aindices[2], aindices[2] + size - 1};

        // A12 and A11 start and end at the same rows
        // A12 starts at the column right after the column where A11 ends
        // The end columns is the same as the end column of the previous partition
        int a12[] = {a11[0], a11[1], a11[3] + 1, aindices[3]};

        // A21 and A11 start and end at the same columns
        // A21 starts at the row right after the row where A11 ends
        // The end row is the same as the end row of the previous partition
        int a21[] = {a11[1] + 1, aindices[1], a11[2], a11[3]};

        // A22 and A21 are similar to A12 and A11
        int a22[] = {a21[0], a21[1], a21[3] + 1, aindices[3]};

        // Since A and B are of the same size, the same partitioning logic is applicable
        // But not that Bij and Aij are NOT necessarily equal
        // They will differ depending on the matrices a and b point to
        int b11[] = {bindices[0], bindices[0] + size - 1, bindices[2], bindices[2] + size - 1};

        int b12[] = {b11[0], b11[1], b11[3] + 1, bindices[3]};

        int b21[] = {b11[1] + 1, bindices[1], b11[2], b11[3]};

        int b22[] = {b21[0], b21[1], b21[3] + 1, bindices[3]};

        // 10 matrices, S1, S2, ..., S10 need to be created
        // This represents the initial range of indices to be considered
        // Note: A separate function is not used since each Si has a different computation
        int sindices[] = {0, size - 1, 0, size - 1};

        // Calculating S1 = B12 - B22
        int* mat = malloc(sizeof(int) * size * size);

        for (int i = 0; i < size; ++i)
            for(int j = 0; j < size; ++j)
                // The indices are "displaced" by the respective partition indices
                // And then scaled according to the size
                // Ensures that we are accessing the correct value with respect to the original matrices (A and B) or any Si
                *((mat + i * size) + j) = *((b + (i + b12[0]) * s2) + j + b12[2]) - *((b + (i + b22[0]) * s2) + j + b22[2]);


        // Recursively calling multiply() to obtain P1 = A11 . S1
        // a11 is passed as aindices since that is the partition of a that we need to consider
        // sindices is passed since we need to consider S1 in its entirety
        // Subsequent recursive calls will partition S1 accordingly
        // s1 was the size of a and the size of 'mat' is 'size'
        // Doing this ensures that we are passing the correct size for scaling purposes
        // For example, for the original matrix A, all partitions of A must use MAX as the scaling size
        int* p1 = multiply(a11, sindices, a, mat, s1, size);

        // Since S1 is not used again, the associated memory is freed
        free(mat);

        // Calculating S2 = A11 + A12
        mat = malloc(sizeof(int) * size * size);

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                *((mat + i * size) + j) = *((a + (i + a11[0]) * s1) + j + a11[2]) + *((a + (i + a12[0]) * s1) + j + a12[2]);

        // Calculating P2 = S2 . B22
        int* p2 = multiply(sindices, b22, mat, b, size, s2);
        free(mat);

        // Calculating S3 = A21 + A22
        mat = malloc(sizeof(int) * size * size);

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                *((mat + i * size) + j) = *((a + (i + a21[0]) * s1) + j + a21[2]) + *((a + (i + a22[0]) * s1) + j + a22[2]);

        // Calculating P3 = S3 . B11
        int* p3 = multiply(sindices, b11, mat, b, size, s2);
        free(mat);

        // Calculating S4 = B21 - B11
        mat = malloc(sizeof(int) * size * size);

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                *((mat + i * size) + j) = *((b + (i + b21[0]) * s2) + j + b21[2]) - *((b + (i + b11[0]) * s2) + j + b11[2]);

        // Calculating P4 = A22 . S4
        int* p4 = multiply(a22, sindices, a, mat, s1, size);
        free(mat);

        // Calculating S5 = A11 + A22 and S6 = B11 + B22
        // Calculated simultaneously in mat and mat1 respectively
        // Since both are needed to calculate P5
        mat = malloc(sizeof(int) * size * size);
        int* mat1 = malloc(sizeof(int) * size * size);

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
            {
                *((mat + i * size) + j) = *((a + (i + a11[0]) * s1) + j + a11[2]) + *((a + (i + a22[0]) * s1) + j + a22[2]);
                *((mat1 + i * size) + j) = *((b + (i + b11[0]) * s2) + j + b11[2]) + *((b + (i + b22[0]) * s2) + j + b22[2]);
            }

        // Calculating P5 = S5 . S6
        int* p5 = multiply(sindices, sindices, mat, mat1, size, size);
        free(mat);
        free(mat1);

        // Calculating S7 = A12 - A22 and S8 = B21 + B22
        mat = malloc(sizeof(int) * size * size);
        mat1 = malloc(sizeof(int) * size * size);

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
            {
                *((mat + i * size) + j) = *((a + (i + a12[0]) * s1) + j + a12[2]) - *((a + (i + a22[0]) * s1) + j + a22[2]);
                *((mat1 + i * size) + j) = *((b + (i + b21[0]) * s2) + j + b21[2]) + *((b + (i + b22[0]) * s2) + j + b22[2]);
            }

        // Calculating P6 = S7 . S8
        int* p6 = multiply(sindices, sindices, mat, mat1, size, size);
        free(mat);
        free(mat1);

        // Calculating S9 = A11 - A12 and S10 = B11 + B12
        mat = malloc(sizeof(int) * size * size);
        mat1 = malloc(sizeof(int) * size * size);

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
            {
                *((mat + i * size) + j) = *((a + (i + a11[0]) * s1) + j + a11[2]) - *((a + (i + a21[0]) * s1) + j + a21[2]);
                *((mat1 + i * size) + j) = *((b + (i + b11[0]) * s2) + j + b11[2]) + *((b + (i + b12[0]) * s2) + j + b12[2]);
            }

        // Calculating P7 = S9 . S10
        int* p7 = multiply(sindices, sindices, mat, mat1, size, size);
        free(mat);
        free(mat1);

        // c is of size n * n
        // It is partitioned in the for loop itself
        // C11 = P5 + P4 - P2 + P6
        // Where C11 = {0, n / 2 - 1, 0, n / 2 - 1}
        for (int i = 0, k = 0; i < size; ++i, ++k)
            for (int j = 0, l = 0; j < size; ++j, ++l)
                *((c + i * n) + j) = *((p5 + k * size) + l) + *((p4 + k * size) + l) - *((p2 + k * size) + l) + *((p6 + k * size) + l);

        // C12 = P1 + P2
        // Where C12 = {C11[0], C11[1], C11[3] + 1, n - 1}
        for (int i = 0, k = 0; i < size; ++i, ++k)
            for (int j = size, l = 0; j < n; ++j, ++l)
                *((c + i * n) + j) = *((p1 + k * size) + l) + *((p2 + k * size) + l);

        // C21 = P3 + P4
        // Where C21 = {C11[1] + 1, n - 1, C11[2], C11[3]}
        for (int i = size, k = 0; i < n; ++i, ++k)
            for (int j = 0, l = 0; j < size; ++j, ++l)
                *((c + i * n) + j) = *((p3 + k * size) + l) + *((p4 + k * size) + l);

        // C22 = P5 + P1 - P3 - P7
        // Where C22 = {C21[0], C21[1], C21[3] + 1, n - 1}
        for (int i = n - size, k = 0; i < n; ++i, ++k)
            for (int j = size, l = 0; j < n; ++j, ++l)
                *((c + i * n) + j) = *((p5 + k * size) + l) + *((p1 + k * size) + l) - *((p3 + k * size) + l) - *((p7 + k * size) + l);

    }
    // Returning the end result
    return c;
}
