#include<stdio.h>
#include<stdlib.h>

void merge(int *leftArr, int lenLeftArr, int *rightArr, int lenRightArr, int *arr){
    int i, j, k;
    i = j = k = 0;
    while (i<lenLeftArr && j<lenRightArr)
    {
        if (leftArr[i] <= rightArr[j])
        {
            arr[k] = leftArr[i];
            k++;
            i++;
        }
        if (leftArr[i] > rightArr[j])
        {
            arr[k] = rightArr[j];
            k++;
            j++;
        }
    }
    while (i<lenLeftArr)
    {
        arr[k] = leftArr[i];
        k++;
        i++;
    }
    while (j<lenRightArr)
    {
        arr[k] = rightArr[j];
        k++;
        j++;
    }
}

void merge_sort(int *arr, int len){
    if (len == 1)
    {
        return;
    }
    else{
        int mid, i=0;
        mid = len/2;
        int *rightArr, *leftArr;
        leftArr = (int *)malloc(mid*sizeof(int));
        rightArr = (int *)malloc((len-mid)*sizeof(int));
        while (i<len)
        {
            if(i<mid)
                leftArr[i] = arr[i];
            else{
                rightArr[i-mid] = arr[i];
            }            
            i++; 
        }
        
        merge_sort(leftArr, mid);
        merge_sort(rightArr, (len-mid));
        merge(leftArr, mid, rightArr, (len-mid), arr);
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

    merge_sort(arr, n);

    printf("Sorted Array:\n| ");
    for (i = 0; i < n; i++)
    {
        printf("%d | ", arr[i]);
    }
    return 0;
}