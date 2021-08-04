#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

//structure for each node of priority queue 
typedef struct VertexWeightPair
{
    int vertex;
    int weight;
}VWpair;

//structure of Priority Queue
typedef struct priorityQueue
{
    int rear;
    int size;
    VWpair **arr;
}pq;

int getParent(int childIdx){
    return (childIdx-1)/2;
}

int getLeftChild(int index, int rear){
    int lc = (2*index)+1;
    if (lc<=rear)
    {
        return lc;
    }
    else{
        return 0;
    }
}

int getRightChild(int index, int rear){
    int rc = (2*index)+2;
    if (rc<=rear)
    {
        return rc;
    }
    else{
        return 0;
    }
}

void swap(int i1, int i2, VWpair **arr){
    VWpair *temp;
    temp = arr[i1];
    arr[i1] = arr[i2];
    arr[i2] = temp;
}

void heapifyAtInsert(int index, VWpair **pqueue){
    if (index == 0)
    {
        return;
    }
    else{
        int largest, largestIdx, parentIdx;
        largest = pqueue[index]->weight;
        parentIdx = getParent(index);
        if (pqueue[parentIdx]->weight > largest)
        {
            largestIdx = parentIdx;
            largest = pqueue[parentIdx]->weight;
        }
        if (largest != pqueue[index]->weight)
        {
            swap(parentIdx, index, pqueue);
            heapifyAtInsert(parentIdx, pqueue);
        } 
    }
}

void heapify(int index, int rear, VWpair **arr){
    int smallest, smallestIdx;
    smallest = arr[index]->weight;
    if (getLeftChild(index, rear) && arr[getLeftChild(index, rear)]->weight < smallest)
    {
        smallestIdx =  getLeftChild(index, rear);
        smallest = arr[smallestIdx]->weight;
    }
    if (getRightChild(index, rear) && arr[getRightChild(index, rear)]->weight < smallest)
    {
        smallestIdx =  getRightChild(index, rear);
        smallest = arr[smallestIdx]->weight;
    }
    if (smallest != arr[index]->weight)
    {
        swap(smallestIdx, index, arr);
        heapify(smallestIdx, rear, arr);
    }    
}

void heapifyOnArr(pq *pqueue){
    int rear = pqueue->rear;
    int currentIdx = rear/2-1, i;
    if (currentIdx < 0)
    {
        currentIdx = 0;
    }
    for (i = currentIdx; i >= 0; i--)
    {
        heapify(i, pqueue->rear, pqueue->arr);
    }
}

void insert(int vertex, int weight, pq *pqueue){
    int size;
    VWpair *node;
    size = pqueue->size;
    if(pqueue->rear < size-1){
        node = (VWpair *)malloc(sizeof(VWpair));
        node->vertex = vertex;
        node->weight = weight;
        pqueue->arr[++pqueue->rear] = node;
        heapifyAtInsert(pqueue->rear, pqueue->arr);
    }
    else{
        printf("Queue is full.");
    }
}

VWpair * extract(pq *pqueue){
    VWpair * ele = pqueue->arr[0];
    int rear = pqueue->rear;
    swap(0, rear, pqueue->arr);
    pqueue->rear--;
    heapifyOnArr(pqueue);
    return ele;
}

int isEmpty(pq *pqueue){ 
    if(pqueue->rear == -1)
        return 1;

    else
        return 0;
}

void primMST(pq *pqueue, int **matrix, int *weight, int *parentKey, int *inMST, int size){
    VWpair *extracted;
    int row, j;
    while (!isEmpty(pqueue))
    {
        extracted = extract(pqueue);
        row = extracted->vertex;

        inMST[row] = 1; // Extracted vertex is included in MST

        for (j = 0; j < size; j++)
        {
            if(matrix[row][j]!=0){
                if (inMST[j] == 0 && weight[j] > matrix[row][j])
                {
                    weight[j] = matrix[row][j];
                    insert(j, weight[j], pqueue);
                    parentKey[j] = row;
                }
            }
        }
    }
    for (j = 1; j < size; j++)
    {
        printf("  %d - %d       %d\n", j, parentKey[j], weight[j]);
    }     
}

int main(void)
{
    int i, j, size;
    int **matrix, *weight, *parentKey, *inMST;
    pq pqueue;
    // Vertex should start from 0
    //No of vertices:
	scanf("%d", &size);
    pqueue.rear = -1;
    pqueue.size = size;
    pqueue.arr = (VWpair **)malloc(size*sizeof(VWpair *));
    weight = (int *)malloc(size*sizeof(int));
    parentKey = (int *)malloc(size*sizeof(int));
    inMST = (int *)calloc(size, sizeof(int));
	matrix = (int**)malloc(sizeof(int*)*size);

    for(i=0;i<size;i++){
		matrix[i]=(int*)malloc(sizeof(int)*size);
        weight[i] = INT_MAX; //Initially all the weightance will be infinity.
        parentKey[i] = -1;
    }

    //Adjacency Matrix:
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
			scanf("%d",&matrix[i][j]);
	}

    insert(0, 0, &pqueue);
    weight[0] = 0;
    printf("\nVertex      Distance \n");
    printf("-------   ------------\n");
    primMST(&pqueue, matrix, weight, parentKey, inMST, size);

    return 0;
}

/*
#Test Case: 1
-----------------------
5
0 2 0 6 0
2 0 3 8 5
0 3 0 0 7
6 8 0 0 9
0 5 7 9 0

*/