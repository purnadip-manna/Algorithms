#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

void parenthesize(int **s, int i, int j) {
    if (i == j)
        printf(" A%d ", i);
    else {
        printf(" ( ");
        parenthesize(s, i, s[i][j]);
        parenthesize(s, s[i][j] + 1, j);
        printf(" ) ");
    }
}

void matrixChainOrder(int *dim, int **cost, int **order, int n){
    int i, j, q, k, level;
    for (level = 1; level < n; level++)
    {
        for (i = 0; i < n-level; i++)
        {
            j = i+level;
            cost[i][j] = INT_MAX;
            for (k = i; k < j; k++)
            {
                q = cost[i][k] + cost[k+1][j] + (dim[i]*dim[k+1]*dim[j+1]);
                if (q < cost[i][j]) {
                    cost[i][j] = q;
                    order[i][j] = k;
                }
            } 
        }    
    }
    printf("\nSequence is :\n");
    parenthesize(order, 0, n-1);
    printf("\nTotal requried multiplication is : %d\n", cost[0][n-1]);
}

int main(void)
{
    int i, j, *dim, n;
    int **cost, **order;

    printf("Enter the no of Matrices: ");
    scanf("%d", &n);
    dim = (int *)malloc(sizeof(int)*(n+1));

    printf("Enter the dimentions: ");
    for (i = 0; i <= n; i++)
        scanf("%d", &dim[i]);
    
    cost = (int **)malloc(sizeof(int *)*n);
    order = (int **)malloc(sizeof(int *)*n);
    for (i = 0; i < n; i++)
    {
        cost[i] = (int *)calloc(n,sizeof(int));
        order[i] = (int *)calloc(n,sizeof(int));
        cost[i][i] = 0;
    }
    matrixChainOrder(dim, cost, order, n);
    return 0;
}

/*

 -------- Case 1: ---------
Input:
4
40 20 30 10 30
Output:
Sequence is :
(  (  A0  (  A1  A2  )  )  A3  )
Total requried multiplication is : 26000 

-------- Case 2: ---------
Input:
4
3 2 4 2 5
Output:
Sequence is :
(  (  A0  (  A1  A2  )  )  A3  )
Total requried multiplication is : 58 

*/