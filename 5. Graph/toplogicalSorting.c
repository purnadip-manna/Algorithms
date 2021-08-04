#include<stdio.h>
#include<stdlib.h>
int *visited;

typedef struct arr
{
    int *arr;
    int index;
}list;


void dfs(int v, int **Graph, int n, list *l){
    int i;
    if(!visited[v]){
        visited[v] = 1;
        for (i = 0; i < n; i++)
        {
            if (Graph[v][i] && !visited[i])
                dfs(i, Graph, n, l);
        }
    }
    l->arr[l->index] = v;
    l->index = l->index-1;

}

int * topSort(int **Graph, int n){
    list l1; int i;
    l1.arr = (int *)malloc(n*sizeof(int));
    l1.index = n-1;
    for (i = 0; i < n; i++)
    {
        if(!visited[i])
            dfs(i, Graph, n, &l1);
    }
    return l1.arr;
}

int main(void)
{
    int *topSortedArr, **Graph, n, i, j;
    scanf("%d", &n);
    Graph = (int **)malloc(n*sizeof(int *)); 
    visited = (int *)calloc(n, sizeof(int));
    for (i = 0; i < n; i++)
    {
        Graph[i] = (int *)malloc(n*sizeof(int));
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &Graph[i][j]);
        }
    }
    topSortedArr = topSort(Graph, n);
    for (i = 0; i < n; i++)
    {
        printf("%d | ", topSortedArr[i]);
    }
    return 0;
}

/*

        (0)   (1)
         \    /|
         \/\/ |/
         (2) (3)
        \/   |
      (4)   |
        \/ |/
        (5)----->(6)

7
0 0 1 0 0 0 0
0 0 1 1 0 0 0
0 0 0 0 1 0 0
0 0 0 0 0 1 0
0 0 0 0 0 1 0
0 0 0 0 0 0 1
0 0 0 0 0 0 0


*/