#include<stdio.h>
#include<stdlib.h>

int noSol;

int isAdj(int u, int **Graph, int colorNo, int *colorPaltte, int n){
    int i;
    for (i = 0; i < n; i++)
    {
        if (colorPaltte[i] == colorNo && Graph[u][i]){
            return 1;
        }
    }
    return 0;
}

void printPalette(int *arr, int n){
    noSol++;
    int i;
    printf("\n");
    for (i = 0; i < n; i++)
    {
        printf("%d | ", arr[i]);
    }
    printf("\n");
}

void graphColoring(int **Graph, int *colorPalette, int startV, int n, int colorNo){
    int i;
    for (i = 1; i <= colorNo; i++)
    {
        if (!isAdj(startV, Graph, i, colorPalette, n))
        {
            colorPalette[startV] = i;
            if(startV == n-1){
                printPalette(colorPalette, n);
            }
            else{
                graphColoring(Graph, colorPalette, startV+1, n, colorNo);
            }
            colorPalette[startV] = 0;
        }   
    }
}

int main(void)
{
    int **Graph, *colorPalette, colorNo, i, j, n;
    scanf("%d", &n);
    Graph = (int**)malloc(n*sizeof(int *));
    colorPalette = (int*)calloc(n,sizeof(int));
    for (i = 0; i < n; i++)
    {
        Graph[i] = (int*)malloc(n*sizeof(int));
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &Graph[i][j]);
        }
    }
    scanf("%d", &colorNo);
    graphColoring(Graph, colorPalette, 0, n, colorNo);
    printf("\n%d", noSol);
    return 0;
}

/*

     (1) [0]---------[1] (3)
         |           |
        |           |
  (3) [3]---------[2] (1)

   Color No ==> 3
   Color Palette ==> [0, 0, 0, 0]
   Sol => 18


input:
4
0 1 0 1
1 0 1 0
0 1 0 1
1 0 1 0
3

*/