#include<stdio.h>
#include<stdlib.h>

int solCount = 0;

int isPlaceAvailable(int row, int col, int *sol)
{
    // Place the Queen at [row, col] position of the board
    // Return 1 (true) if Queen can be placed at [row, col] else return 0 (false)
    //i in range(0, row)

    int i;
    for (i = 0; i < row; i++)
    {
        if (sol[i] == col || abs(sol[i]-col) == abs(i-row))
        {
            return 0;
        }
    }
    return 1;
}

void printSol(int *sol, int n){
    int i;
    printf("\nSol: |");
    for (i = 0; i < n; i++)
    {
        printf("%d | ", sol[i]);
    }
    printf("\n");
}

void printBoard(int *sol, int n){
    int i, j;
    printf("\n");
    for (i = 0; i < n; i++)
    {
        printf("\n|");
        for (j = 0; j < n; j++)
        {
            if (sol[i] == j)
            {
                printf(" Q |");
            }
            else{
                printf("   |");
            }
            
        }
        printf("\n");
    }
}

void NQueens(int row, int n, int *sol)
{
    int j;
    for (j = 0; j < n; j++)
    {    
        if (isPlaceAvailable(row, j, sol)){
            //printf("\nsol[%d] = %d\n", row, j);
            sol[row] = j;
            if (row == n-1)
            {
                printSol(sol, n);
                printBoard(sol, n);
                printf("\n");
                solCount++;
            }
            else
                NQueens(row+1, n, sol);
        }
    }
    return;
}

int main(void)
{
    int n, i, j, *sol;
    printf("Size of Board: ");
    scanf("%d", &n);                    // n : number of Queens
    sol = (int *)malloc(n*sizeof(int));// sol[] : store the column position of each row where the Queen has been placed
    for (i = 0; i < n; i++)
    {
        sol[i] = -1;
    }  
    NQueens(0, n, sol);
    printf("No of Sol: %d", solCount);
    return 0;
}