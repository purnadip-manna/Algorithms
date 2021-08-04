#include<stdio.h>
#include<stdlib.h>
#include <limits.h>

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

void print(){
	int i, size;
	size = stk->top;
	for (i = 0; i <= size; ++i)
	{
		printf(" %d |", stk->arr[i]);
	}
	printf("\n");
}

/*		<=== End of Stack ===>		*/

// tsp(vertex, {V} - vertex) = min(cost[vertex][k] + tsp(k, {V} - {vertex, k} ))

int tsp(int startV, int vertex, int *setOfAvaV, int **Cost, int level, int n){
	level++;
	int i;
	for (i = 0; i <= level; i++)
	{
		printf("\t");
	}
	printf("Call(%d)\n", vertex);

	setOfAvaV[vertex] = 0;

	int temp, k ,flag = 1, min = INT_MAX, minForV;
	for (k = 0; k < n; k++)
	{
		if(setOfAvaV[k] != 0 && Cost[vertex][k] != 0){
			push(k);
			temp = tsp(startV, k, setOfAvaV, Cost, level, n) + Cost[vertex][k];
			pop();
			//printf("(%d < %d)\n", temp, min);
			if(temp < min){
				min = temp;
				minForV = k;
				//printf("%d | ", k);
			}
			flag = 0;
		}
	}
	setOfAvaV[vertex] = 1;
	if(flag){
		//printf("(%d) --> (%d) Final Cost: %d\n", vertex, startV, Cost[vertex][startV]);
		print();
		return Cost[vertex][startV];
	}
	return min;
}


int main(void)
{
    int **Cost, *setOfV, n, i, j, startV;
    printf("Enter the Vertex no: ");
    scanf("%d", &n);
    stackInit(n);
    printf("Enter the Cost Matrix:\n");
    Cost = (int **)malloc(n*sizeof(int *));
    setOfV = (int *)malloc(n*sizeof(int));
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
    printf("Cost: %d", tsp(startV, startV, setOfV, Cost, -1, n));
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