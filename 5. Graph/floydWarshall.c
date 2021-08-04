#include<stdio.h>
#include<stdlib.h>
#define INF 9999
void display(int **matrix, int n, int flag){
    int i, j;
    for (i = 0; i < n; i++)
    {
        printf("|");
        for (j = 0; j < n; j++)
        {
            if(matrix[i][j] > 9000)
                printf(" INF |");
            else if(matrix[i][j] == -1 && flag)
                printf(" NIL |");
            else
                printf(" %3d |", matrix[i][j]);
        }
        printf("\n");
    }
}

void floydWarshall(int **Graph, int **piMatrix, int n){
    int i, j, k;
    for (k = 0; k < n; k++)
    {
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                if(Graph[i][j] > (Graph[i][k] + Graph[k][j])){
                    Graph[i][j] = (Graph[i][k] + Graph[k][j]);
                    piMatrix[i][j] = k;
                }
            } 
        }
    }
}

int main(void)
{
    int **Graph, **piMatrix, n, i, j, temp;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    Graph = (int **)malloc(n*sizeof(int *));
    piMatrix = (int **)malloc(n*sizeof(int *));
    for (i = 0; i < n; i++)
    {
        Graph[i] = (int *)malloc(n*sizeof(int));
        piMatrix[i] = (int *)malloc(n*sizeof(int));
    }
    printf("Enter the Adjacency Matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &temp);
            Graph[i][j] = temp;
            if (temp != 0 && temp != INF)
            {
                piMatrix[i][j] = i;
            }
            else{
                piMatrix[i][j] = -1;
            }
        } 
    }
    floydWarshall(Graph, piMatrix, n); 
    printf("\nD-Matrix:\n");
    display(Graph, n, 0);
    printf("\nPi-Matrix:\n");
    display(piMatrix, n, 1);
    return 0;
}

/*
input:
4
0 3 9999 7
8 0 2 9999
5 9999 0 1
2 9999 9999 0

intput:
5
0 3 8 9999 -4
9999 0 9999 1 7
9999 4 0 9999 9999
2 9999 -5 0 9999
9999 9999 9999 6 0

*/