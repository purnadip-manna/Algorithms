#include<stdio.h>
#include<stdlib.h>
#define max 20
#define MAX 100
int find(int i,int *parent)
{
   	while(parent[i])
   		i=parent[i];
   	return i;
}
int unify(int i,int j,int *parent)
{
   	if(i!=j)
   	{
   		parent[j]=i;
   		return 1;
   	}
   	return 0;
}
void kruskal(int size,int **adjMatrix,int *parent,int minCost,int chk){
	int min=0,r=0,c=0,i=0,j=0;
	while(chk<=size+max){
		for( i=1,min=MAX;i<=size;i++){
			for( j=1;j<=size;j++){
				if(min>adjMatrix[i][j] && adjMatrix[i][j]!=0){
					min=adjMatrix[i][j];
					r=i;
					c=j;
				}
			}
		}
		if(unify(find(r,parent),find(c,parent),parent)){
			minCost+=adjMatrix[r][c];
		}
		adjMatrix[r][c]=adjMatrix[c][r]=MAX;
		chk++;
	}
	printf("%d",minCost);
}
int main(){
	int size=0,minCost=0,chk=1,**adjMatrix,*parent,i=0,j=0;
	scanf("%d",&size);
	parent=(int *)malloc((size+1)*sizeof(int));
	adjMatrix=(int **)malloc((size+1)*sizeof(int *));
	for(i=0;i<=size;i++){
		adjMatrix[i]=(int *)malloc((size+1)*sizeof(int));
	}
	for(i=0;i<=size;i++){
		parent[i]=0;
	}
	for(i=1;i<=size;i++){
		for(j=1;j<=size;j++){
			scanf("%d",&adjMatrix[i][j]);
			if(adjMatrix[i][j]==0){
				adjMatrix[i][j]=MAX;
			}
		}
	}
	kruskal(size,adjMatrix,parent,minCost,chk);
}