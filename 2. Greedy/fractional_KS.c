#include<stdio.h>
#include<stdlib.h>

int findMaxRatio(float *arr, int n){
    int i, index;
    float temp;
    temp = -1;
    for (i = 0; i < n; i++)
    {
        if (temp < arr[i])
        {
            temp = arr[i];
            index = i;
        }  
    }
    return index;
}

int main(void)
{
    int i, index, capacity, n, *profits, *weights, remainingWt, maxProfit=0;
    float *pwRatio, temp1, temp2;
    scanf("%d", &capacity);
    scanf("%d", &n);
    profits = (int *)malloc(n*sizeof(int));
    weights = (int *)malloc(n*sizeof(int));
    pwRatio = (float *)malloc(n*sizeof(float));
    for (i = 0; i < n; i++)
    {
        scanf("%d", &profits[i]);
    }
    for (i = 0; i < n; i++)
    {
        scanf("%d", &weights[i]);
    }
    for (i = 0; i < n; i++)
    {
        temp1 = profits[i];
        temp2 = weights[i];
        pwRatio[i] = (temp1/temp2);
    }
    remainingWt = capacity;
    while (remainingWt)
    {
        index = findMaxRatio(pwRatio, n);
        if(remainingWt-weights[index] < 0){
            maxProfit = maxProfit + (remainingWt)*pwRatio[index];
            remainingWt = 0;
        }
        else{
            maxProfit += profits[index];
            remainingWt -= weights[index];
        }
        pwRatio[index] = -1;
    }
    printf("%d", maxProfit);
    return 0;
}

/*
Test Case: 
15
7
5 10 15 7 8 9 4
1 3 5 4 1 3 2

20
3
180 150 100
20 10 4

*/
