#include<stdio.h>
#include<stdlib.h>

void swap(int *arr, int i, int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int partition(int *arr, int start, int end){
    int pIndex = 0, i, pivot = arr[end];
    for (i = 0; i < end; i++)
    {
        if (arr[i]<=pivot)
        {
            swap(arr, i, pIndex);
            pIndex++;
        }
    }
    swap(arr, pIndex, end);
    return pIndex;
}

void quick_sort(int *arr, int left, int right){
    if(left<right){
        int pIndex;
        pIndex = partition(arr, left, right);
        quick_sort(arr, left, pIndex-1);
        quick_sort(arr, pIndex+1, right);
    }
}

int main(void)
{
    int i, j, key, n, *arr;
    printf("Size: ");
    scanf("%d", &n);
    arr = (int *)malloc(n*sizeof(int));
    printf("Enter the elements: ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    quick_sort(arr, 0, n-1);

    printf("Sorted Array:\n| ");
    for (i = 0; i < n; i++)
    {
        printf("%d | ", arr[i]);
    }
    return 0;
}