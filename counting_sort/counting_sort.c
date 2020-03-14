#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

// Function prototype which sorts a and stores the result in b
void count_sort(int a[], int b[], int maximum);
// Function prototype which takes the array as input from the user
// It also returns the maximum value in the array
int input(int*);

int main(void)
{
    int array[SIZE], sorted[SIZE];

    // Getting the array and the maximum in the array
    int maximum = input(array);

    // Sorting the array
    count_sort(array, sorted, maximum);

    // Printing the result
    printf("Sorted array: ");
    for (int i = 0; i < SIZE; ++i)
        printf("%d ", sorted[i]);

    printf("\n");

    return 0;
}

// Function definition for input
int input(int array[])
{
    /*
    Function which takes the array as input from the user
    It also computes the maximum value in the array

    Parameters:
        array: int array, the array to be sorted

    Return value:
        maximum: int, the maximum value in array
    */

    int maximum = 0, val;

    printf("Enter the array: ");
    for (int i = 0; i < SIZE; ++i)
    {
        scanf("%d", &val);

        if (val > maximum)
            maximum = val;

        array[i] = val;
    }

    return maximum;
}

// Function definition for count_sort
void count_sort(int array[], int sorted[], int maximum)
{
    /*
    Function which takes an array and sorts it using Counting Sort

    The Counting Sort method can be looked at here:
    https://en.wikipedia.org/wiki/Counting_sort

    Parameters:
        array: int array, the array to be sorted
        sorted: int array, stores the resultant sorted array
        maximum: int, the maximum value in array

    Return value:
        void
    */

    // If the maximum is 'maximum', we need to have enough space in the counting array
    // To store 0 to maximum. Hence, +1
    int n = maximum + 1;

    // This array stores the count of each element
    // calloc(n, x) initializes a pointer of to a block of n elements
    // With each element having a size of x
    // The advantage is that each element of the block is initialized to 0
    int* counts = calloc(n, sizeof(int));

    // Calculating the count of each element
    // If the element is x, its count is stored in counts[x]
    // Thus, the index in counts corresponds to the element
    for (int i = 0; i < SIZE; ++i)
        counts[array[i]] += 1;

    /*
    Calculating the number of elements less than or equal to an element for each element
    This is very similar to computing cumulative frequencies
    The indices of counts are "sorted" by default
    Thus, the 0th index is the smallest element in the parameter array (corresponding to the value 0)
    The 1st index corresponds to the value 1 in the parameter array
    The number of elements less than or equal to 1 is the number of 0's (i - 1) in array + the number of 1's (i) in array
    The 2nd index corresponds to the value 2 in the parameter array
    The number of elements less than or equal to 2 (i) is the number of 0's + number of 1's + number of 2's
    But, number of 0's + number of 1's has already been updated into counts[1] (i - 1)
    Hence, taking i and the i - 1 is sufficient, similar to cumulative frequencies
    */
    for (int i = 1; i < n; ++i)
        counts[i] = counts[i] + counts[i - 1];

    /*
    The result is updated using the count
    array[i] will give the i-th element in the array
    counts[array[i]] will give the cumulative count of the ith element
    If the count is x, the sorted position of the element is x - 1
    There is a -1 as C has 0-indexed arrays
    If the size of the array is 10 and the cumulative count of an element is also 10
    It is the largest element (as it counts itself as well) and needs to in index 9 of the result
    The loop is reversed to make the sort STABLE
    A stable sort is one where numbers with the same value appear in the output in the same order as the input
    That is, if there are two 5's with indices i and j such that  i < j in the input
    The output is going to place the two 5's in indices a and b such that a < b
    Stability is important only because Counting Sort is generally used in Radix Sort, which requires stability
    Otherwise, the direction of the loop doesn't matter
    */
    for (int i = SIZE - 1; i >= 0; i--)
    {
        sorted[counts[array[i]] - 1] = array[i];
        // The cumulative count is reduced by 1 to handle non-distinct entires
        // If there are two 5's in the array, not decreasing the count will result in both 5's in the same index
        // Thus, the result will have only one 5
        // This can intuitively be thought of as marking that one instance of the i-th element has been correctly placed
        counts[array[i]] -= 1;
    }
}
