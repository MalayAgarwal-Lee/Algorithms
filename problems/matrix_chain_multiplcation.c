#include <stdio.h>
#include <limits.h>
#define MAT_COUNT 6

void optimal_parenthesize(int dims[], int m[][MAT_COUNT], int s[][MAT_COUNT - 1], int i, int j);
void print_optimal_parenthesization(int s[][MAT_COUNT - 1], int i, int j);

int main(int argc, char const *argv[])
{
    int dims[MAT_COUNT + 1];
    int m[MAT_COUNT][MAT_COUNT], s[MAT_COUNT - 1][MAT_COUNT - 1];

    printf("Enter the dimensions of the matrices as an array (p0 p1 ... pn): ");
    for (int i = 0; i < MAT_COUNT + 1; ++i)
        scanf("%d", &dims[i]);


    optimal_parenthesize(dims, m, s, 0, MAT_COUNT - 1);

    printf("Optimal number of multiplications: %d\n", m[0][MAT_COUNT - 1]);

    printf("Optimal parenthesizaton: ");
    print_optimal_parenthesization(s, 0, MAT_COUNT - 1);

    printf("\n");

    return 0;
}

void optimal_parenthesize(int dims[], int m[][MAT_COUNT], int s[][MAT_COUNT - 1], int i, int j)
{
    for (int i = 0; i < MAT_COUNT; ++i)
        m[i][i] = 0;

    for (int l = 2; l <= MAT_COUNT; ++l)
    {
        for (int i = 0; i < MAT_COUNT - l + 1; ++i)
        {
            int j = i + l - 1;

            m[i][j] = INT_MAX;

            for (int k = i; k < j; ++k)
            {
                int cost = m[i][k] + m[k + 1][j] + dims[i] * dims[k + 1] * dims[j + 1];
                if (cost < m[i][j])
                {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }
}

void print_optimal_parenthesization(int s[][MAT_COUNT - 1], int i, int j)
{
    if (i == j)
        printf("A%d", i);
    else
    {
        printf("(");
        print_optimal_parenthesization(s, i, s[i][j]);
        print_optimal_parenthesization(s, s[i][j] + 1, j);
        printf(")");
    }
}



