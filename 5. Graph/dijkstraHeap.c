#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

//structure for each node of priority queue 
typedef struct VertexDistancePair
{
    int vertex;
    int dist;
}VDpair;

//structure of Priority Queue
typedef struct priorityQueue
{
    int rear;
    int size;
    VDpair **arr;
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

void swap(int i1, int i2, VDpair **arr){
    VDpair *temp;
    temp = arr[i1];
    arr[i1] = arr[i2];
    arr[i2] = temp;
}

void heapifyAtInsert(int index, VDpair **pqueue){
    if (index == 0)
    {
        return;
    }
    else{
        int smallest, smallestIdx, parentIdx;
        smallest = pqueue[index]->dist;
        parentIdx = getParent(index);
        if (pqueue[parentIdx]->dist < smallest)
        {
            smallestIdx = parentIdx;
            smallest = pqueue[parentIdx]->dist;
        }
        if (smallest != pqueue[index]->dist)
        {
            swap(parentIdx, index, pqueue);
            heapifyAtInsert(parentIdx, pqueue);
        } 
    }
}

void heapify(int index, int rear, VDpair **arr){
    int largest, largestIdx;
    largest = arr[index]->dist;
    if (getLeftChild(index, rear) && arr[getLeftChild(index, rear)]->dist >largest)
    {
        largestIdx =  getLeftChild(index, rear);
        largest = arr[largestIdx]->dist;
    }
    if (getRightChild(index, rear) && arr[getRightChild(index, rear)]->dist >largest)
    {
        largestIdx =  getRightChild(index, rear);
        largest = arr[largestIdx]->dist;
    }
    if (largest != arr[index]->dist)
    {
        swap(largestIdx, index, arr);
        heapify(largestIdx, rear, arr);
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

void insert(int vertex, int dist, pq *pqueue){
    int size;
    VDpair *node;
    size = pqueue->size;
    if(pqueue->rear < size-1){
        node = (VDpair *)malloc(sizeof(VDpair));
        node->vertex = vertex;
        node->dist = dist;
        pqueue->arr[++pqueue->rear] = node;
        heapifyAtInsert(pqueue->rear, pqueue->arr);
    }
    else{
        printf("Queue is full.");
    }
}

VDpair * extract(pq *pqueue){
    VDpair * ele = pqueue->arr[0];
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

void dijkstra(pq *pqueue, int **matrix, int *dist, int size){
    VDpair *extracted;
    int row, j;
    while (!isEmpty(pqueue))
    {
        extracted = extract(pqueue);
        row = extracted->vertex;
        for (j = 0; j < size; j++)
        {
            if(matrix[row][j]!=0){
                if (dist[j] > (extracted->dist + matrix[row][j]))
                {
                    dist[j] = extracted->dist + matrix[row][j];
                    insert(j, dist[j], pqueue);
                }
            }
        }
    }
    for (j = 0; j < size; j++)
    {
        printf("   %d            %d\n", j, dist[j]);
    }     
}

int main(void)
{
    int i, j, size, startingV;
    int **matrix, *dist;
    pq pqueue;
    // Vertex should start from 0
    //No of vertices:
	scanf("%d", &size);
    pqueue.rear = -1;
    pqueue.size = size;
    pqueue.arr = (VDpair **)malloc(size*sizeof(VDpair *));
    dist = (int *)malloc(size*sizeof(int));
	matrix = (int**)malloc(sizeof(int*)*size);

    for(i=0;i<size;i++){
		matrix[i]=(int*)malloc(sizeof(int)*size);
        dist[i] = INT_MAX; //Initially all the distance will be infinity.
    }

    //Adjacency Matrix:
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
			scanf("%d",&matrix[i][j]);
	}

    //starting vertex:
    scanf("%d", &startingV);

    insert(startingV, 0, &pqueue);
    dist[startingV] = 0;
    printf("\nVertex     Distance from vertex %d\n", startingV);
    printf("-------   -------------------------\n");
    dijkstra(&pqueue, matrix, dist, size);

    return 0;
}