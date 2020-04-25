#include <stdio.h>
#include <stdlib.h>


typedef struct arr
{
    int* array;
    int size;
}ARRAY;


void input_array(ARRAY*);
int binary_search(ARRAY*, int, int, int);


int main(int argc, char const *argv[])
{
    ARRAY a;
    int key;

    input_array(&a);

    printf("Enter the element to be searched: ");
    scanf("%d", &key);

    int index = binary_search(&a, key, 0, a.size);

    if (index != -1)
        printf("The element was found at index %d\n", index);
    else
        printf("The element is not in the array\n");

    return 0;
}


void input_array(ARRAY* a)
{
    printf("Enter the size of the array: ");
    scanf("%d", &a->size);

    a->array = (int*)malloc(sizeof(int) * a->size);

    printf("Enter the elements of the array (in sorted order): ");
    for (int i = 0; i < a->size; ++i)
        scanf("%d", &a->array[i]);
}


int binary_search(ARRAY* a, int key, int low, int high)
{
    if (low > high)
        return -1;

    int mid = (low + high) / 2;

    if (key == a->array[mid])
        return mid;
    if (key < a->array[mid])
        return binary_search(a, key, low, mid - 1);
    return binary_search(a, key, mid + 1, high);
}
