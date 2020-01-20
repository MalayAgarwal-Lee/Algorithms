#include <stdio.h>
#define M 7
#define N 5

void input(int a[][N], int*);
int min_index(int*, int row, int start, int end);
void leftmost_mins(int*, int*, int*, int);

int main(int argc, char const *argv[])
{
    int array[M][N], minimums[M], rows[M];
    input(array, rows);

    leftmost_mins((int*)array, rows, minimums, M);

    for (int i = 0; i < M; ++i)
        printf("%d ", minimums[i]);

    return 0;
}

void input(int a[][N], int rows[])
{
    printf("Enter the array: \n");
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < N; ++j)
            scanf("%d", &a[i][j]);

        rows[i] = i;
    }
}

int min_index(int* array, int row, int start, int end)
{
    int minimum = start;

    for (int i = start; i <= end; ++i)
        if (*((array + row * N) + i) < *((array + row * N) + minimum))
            minimum = i;

    return minimum;
}

void leftmost_mins(int* array, int rows[], int minimums[], int nrows)
{
    if (nrows == 1)
        minimums[0] = min_index(array, 0, 0, N - 1);
    else
    {
        int size = (nrows % 2 == 0)? nrows / 2: nrows / 2 + 1;
        int new_rows[size];

        for (int i = 0; i < size; ++i)
            new_rows[i] = rows[2 * i];

        leftmost_mins(array, new_rows, minimums, size);

        for (int i = 1; i < nrows - 1; i += 2)
            minimums[rows[i]] = min_index(array, rows[i], minimums[rows[i - 1]], minimums[rows[i + 1]]);

        if (nrows % 2 == 0)
            minimums[rows[nrows - 1]] = min_index(array, rows[nrows - 1], minimums[rows[nrows - 2]], N - 1);

    }
}

