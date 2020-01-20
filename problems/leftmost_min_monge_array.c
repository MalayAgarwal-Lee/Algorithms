#include <stdio.h>
#define M 7
#define N 5

// Function prototype to take input
void input(int a[][N], int*);

// Function prototype to find index of min. element in 1D-array
int min_index(int*, int row, int start, int end);

// Function to recursively find the leftmost minimum elements
void leftmost_mins(int*, int*, int*, int);

int main(int argc, char const *argv[])
{
    int array[M][N], minimums[M], rows[M];

    // Taking input
    input(array, rows);

    // Making the first call to begin recursion
    // rows represents the current rows that we need to consider
    leftmost_mins((int*)array, rows, minimums, M);

    // Printing the result
    for (int i = 0; i < M; ++i)
        printf("%d ", minimums[i]);

    return 0;
}

void input(int a[][N], int rows[])
{
    /*
    Function which takes the Monge array from the user
    Also, initializes the rows array to <0, 1, ..., M>

    Parameters:
        a: M X N array where the Monge array will be stored
        rows: M-dimensional vector, initialized as <0, 1, ..., M>
    */

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
    /*
    Function which finds the index of the smallest element in a 1D array

    Parameters:
       array: int pointer, storing a reference to the original 2D Monge array
       row: int, the row whose smallest element's index needs to be found
       start: int, the column where the search should start
       end: int, the column where the search should end (inclusive)

    Returns:
        minimum: int, the index of the smallest element
    */

    int minimum = start;

    // We use start and end due to the useful property of Monge arrays:
    // If f(i) is defined the index of the smallest element for ith row
    // Then, f(1) <= f(2) <= ... <= f(M)
    // Thus, for a row i, if we have f(i - 1) and f(i + 1)
    // We only need to look between those to find f(i)
    for (int i = start; i <= end; ++i)
        // array points to the original 2D Monge array and hence, is accessed in this manner
        if (*((array + row * N) + i) < *((array + row * N) + minimum))
            minimum = i;

    return minimum;
}

void leftmost_mins(int* array, int rows[], int minimums[], int nrows)
{
    /*
    Function which computes the index of the leftmost smallest elements for each row in a Monge array recursively

    Parameters:
        array: int pointer, pointer to the M X N Monge array
        rows: int array, representing the rows in the current "half" of the original array
        minimums: int array, storing the minimum index for the ith row in its ith index
        nrows: int, representing the size of the current "half" of the original array
    */

    if (nrows == 1)
        // In the base case, we are calculating the minimum of the first row of the array
        minimums[0] = min_index(array, 0, 0, N - 1);
    else
    {
        // The algorithm is based on the following technique
        // First, we find the minimum index for all the even rows recursively
        // We then compute the indices of the odd rows using the property
        // f(2i) <= f(2i + 1) <= f(2i + 2)
        // That is, to determine the minimum index for the odd row, it is sufficient to look between the minimum of the two even rows above and below it
        // Since we need to compute the minimum indices for all even rows recursively
        // The array rows is used to store the current set of rows in terms of the original array
        // That are part of the halved array
        // new_rows stores these for the next half of the array
        // This eliminates the need to copy the array every time and we can simply make use of the pointer to the original array
        int size = (nrows % 2 == 0)? nrows / 2: nrows / 2 + 1;
        int new_rows[size];

        // new_rows is inititalized with the new even rows based on the old even rows
        for (int i = 0; i < size; ++i)
            new_rows[i] = rows[2 * i];

        // The function is called to compute the minimum indices in these new even rows
        leftmost_mins(array, new_rows, minimums, size);

        // Then, the computed even rows are used to compute the minimum indices for the old even rows
        // In the context of a particular recursive call, the "even rows" are even or odd for that particular half of the array
        // For example, consider a matrix of dimensions 5 X 4
        // The array's size will change as follows, with corresponding rows
        // 5 - {0, 1, 2, 3, 4}; 3 - {0, 2, 4}; 2 - {0, 4}; 1 - {0} (base case)
        // For 2, the even row is 0 and the odd row is 4
        // Note: minimums is indexed using the value of rows since this is the same minimum passed at the first recursive call
        // The minimum index for the ith row needs to be placed at the ith index of minimums
        for (int i = 1; i < nrows - 1; i += 2)
            minimums[rows[i]] = min_index(array, rows[i], minimums[rows[i - 1]], minimums[rows[i + 1]]);

        // If the number of rows is even, the last row will be an even row in terms of the original array
        // Hence, there is no value after it to act as the "end" parameter in min_index()
        // Thus, this case is handled differently, by specifying end as N - 1 (number of columns)
        // Consider the 2 - {0, 4} case in the above example
        // The base case will assign minimum[0] a value but the above loop will not run since the condition is not met
        // Instead, this case will be executed and the statement will basically become
        // minimums[rows[1]] = min_index(array, rows[1]), minimums[rows[0]], N - 1)
        // Which is, minimums[4] = min_index(array, 4, minimums[0], N - 1)
        // Since 0 is the even row and 4 is the odd row in this iteration, this is the correct representation
        if (nrows % 2 == 0)
            minimums[rows[nrows - 1]] = min_index(array, rows[nrows - 1], minimums[rows[nrows - 2]], N - 1);

    }
}

