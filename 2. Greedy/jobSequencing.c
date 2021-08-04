#include<stdio.h>
#include<stdlib.h>

typedef struct jobSeq
{
    int id;
    int profit;
    int deadline;
}job;

void merge(job *leftArr, int lenLeftArr, job *rightArr, int lenRightArr, job *arr){
    int i, j, k;
    i = j = k = 0;
    while (i<lenLeftArr && j<lenRightArr)
    {
        if (leftArr[i].profit >= rightArr[j].profit)
        {
            arr[k] = leftArr[i];
            k++;
            i++;
        }
        if (leftArr[i].profit < rightArr[j].profit)
        {
            arr[k] = rightArr[j];
            k++;
            j++;
        }
    }
    while (j<lenRightArr)
    {
        arr[k] = rightArr[j];
        k++;
        j++;
    }
    while (i<lenLeftArr)
    {
        arr[k] = leftArr[i];
        k++;
        i++;
    } 
}

void merge_sort(job *arr, int len){
    if (len == 1)
    {
        return;
    }
    else{
        int mid, i=0;
        mid = len/2;
        job *rightArr, *leftArr;
        leftArr = (job *)malloc(mid*sizeof(job));
        rightArr = (job *)malloc((len-mid)*sizeof(job));
        while (i<len)
        {
            if(i<mid)
                leftArr[i] = arr[i];
            else
                rightArr[i-mid] = arr[i];
           
            i++; 
        }
        
        merge_sort(leftArr, mid);
        merge_sort(rightArr, (len-mid));
        merge(leftArr, mid, rightArr, (len-mid), arr);
    }
}


int main(void)
{
    int i, j, n, deadline, maxDl=-1, *jobSelected;
    job *jobArr;
    printf("No of jobs: ");
    scanf("%d", &n);
    jobArr = (job *)malloc(n*sizeof(job));
    printf("Enter the profits: ");
    for (i = 0; i < n; i++)
    {
        jobArr[i].id = (i+1);
        scanf("%d", &jobArr[i].profit);
    }
    printf("Enter the Deadlines: ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &deadline);
        jobArr[i].deadline = deadline;
        if(maxDl < deadline){
            maxDl = deadline;
        }
    }

    //printf("Highest Deadline: %d\n\n", maxDl);
    //Sorting the Jobs by the profits in descending order
    merge_sort(jobArr, n);

    jobSelected = (int *)calloc(maxDl, sizeof(int));
    for (i = 0; i < n; i++)
    {
        if (jobSelected[jobArr[i].deadline - 1] == 0)
        {
            jobSelected[jobArr[i].deadline - 1] = jobArr[i].id;
        }
        else{
            j = jobSelected[jobArr[i].deadline - 1] - 1;
            while (j >= 0)
            {
                if (jobSelected[j] == 0)
                {
                    jobSelected[j] = jobArr[i].id;
                    break;
                }
                
                j--;
            }        
        }
    }
    for (i = 0; i < maxDl; i++)
    {
        printf(" J%d | ", jobSelected[i]);
    }    
    return 0;
}

/*

input:
5
20 15 10 5 1
2 2 1 3 3

output:
 J2 |  J1 |  J4 |


input:
7
35 30 25 20 15 12 5
3 4 4 2 3 1 2

output:
 J4 |  J3 |  J1 |  J2 |

input:
7
30 35 25 5 12 15 20
4 3 4 2 1 3 2

output:
 J3 |  J7 |  J2 |  J1 |

*/