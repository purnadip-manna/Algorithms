#include<stdio.h>
#include<stdlib.h>
#include <limits.h>

int minPath = INT_MAX;

/*		<==== Stack ===>		*/
typedef struct s
{
	int *arr, top, size;
}stack;
stack *stk;

void stackInit(int n){
	stk = (struct s *)malloc(sizeof(struct s));
	stk->arr = (int *)malloc(n*sizeof(int));
	stk->top = -1;
	stk->size = n;
}

void push(int ele){
	if (stk->top == stk->size-1)
	{
		return;
	}
	else{
		stk->top++;
		stk->arr[stk->top] = ele;
	}
}

void pop(){
	if (stk->top != -1)
	{
		stk->top--;
	}
}

void stackCopy(int *arr){
	int i, size;
	size = stk->top;
	for (i = 0; i <= size; ++i)
	{
		arr[i] = stk->arr[i];
	}
}

/*		<=== End of Stack ===>		*/

// tsp(vertex, {V} - vertex) = min(cost[vertex][k] + tsp(k, {V} - {vertex, k} ))

void tsp(int startV, int vertex, int *setOfAvaV, int **Cost, int n, int pathValue, int *finalPath){
	setOfAvaV[vertex] = 0;
	int i, flag = 1;
	for (i = 0; i < n; i++)
	{
		if (setOfAvaV[i] != 0 && Cost[vertex][i] != 0)
		{
			push(i);
			//printf("%d --> %d || %d+%d \n", vertex, i, pathValue, Cost[vertex][i]);
			tsp(startV, i, setOfAvaV, Cost, n, pathValue+Cost[vertex][i], finalPath);
			pop();
			flag = 0;
		}
	}
	setOfAvaV[vertex] = 1; 
	if(flag){
		pathValue = pathValue+Cost[vertex][startV];
		if (pathValue < minPath)
		{
			minPath = pathValue;
			stackCopy(finalPath);
		}
	}
}


int main(void)
{
    int **Cost, *setOfV, *finalPath, n, i, j, startV;
    printf("Enter the Vertex no: ");
    scanf("%d", &n);
    stackInit(n);
    printf("Enter the Cost Matrix:\n");
    Cost = (int **)malloc(n*sizeof(int *));
    setOfV = (int *)malloc(n*sizeof(int));
    finalPath = (int *)malloc(n*sizeof(int));
    for (i = 0; i < n; i++)
    {
        Cost[i] = (int *)malloc(n*sizeof(int));
        setOfV[i] = 1;
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &Cost[i][j]);
        }
    }
    printf("Enter the Start Vertex: ");
    scanf("%d", &startV);
    push(startV);
    tsp(startV, startV, setOfV, Cost, n, 0, finalPath);
    printf("Cost: %d", minPath);
    printf("\n");
    for (i = 0; i < n; ++i)
    {
    	printf(" %d |", finalPath[i]);
    }
    return 0;
}

/*

4
0 10 15 20
5 0 9 10
6 13 0 12
8 8 9 0
0

*/