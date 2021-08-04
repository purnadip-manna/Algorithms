/* Longest Common Subsequence */
#include<stdio.h>
#include<stdlib.h>

int max(int a, int b){
	return (a>b)?a:b;
}

int main(void){
	char *str1, *str2, *lcs;
	int len1, len2, i, j, k, temp, m, n, **memo;
	printf("Length of string1: ");
	scanf("%d", &len1);
	m = len1+1;
	str1 = (char*)malloc(m*sizeof(char));
	printf("1st String: ");

	getchar();
	fgets(str1, m, stdin);

	getchar();
	printf("Length of string2: ");
	scanf("%d", &len2);
	n = len2+1;
	str2 = (char*)malloc(n*sizeof(char));
	lcs = (char*)malloc(len2*sizeof(char));

	printf("2nd String: ");
	getchar();
	fgets(str2, n, stdin);

	memo = (int **)malloc(n*sizeof(int *));
	for(i=0; i<n; i++){
		memo[i] = (int *)malloc(m*sizeof(int));
	}
	for(i=0; i<m; i++){
		memo[0][i] = 0;
	}
	for(i=0; i<n; i++){
		memo[i][0] = 0;
	}

	for(i = 1; i<n; i++){
		for(j = 1; j<m; j++){
			if(str2[i-1] == str1[j-1]){
				memo[i][j] = 1+memo[i-1][j-1];
			}
			else{
				memo[i][j] = max(memo[i-1][j], memo[i][j-1]);
			}
		}
	}

	k=0;
	m = m-1;
	for(i = n-1; i>=0; i--){
		temp = memo[i][m];
		for(j = m; j>=0; j--){
			if(memo[i][j]<temp)
			{
				lcs[k] = str1[j];
				k++;
				m = j;
				break;
			}
		}
	}
	m = len1+1;
	printf("\nMemo Table:\n");
	printf("\n - | ");
	for(i=0; i<len1; i++)
		printf("%c | ", str1[i]);

	printf("\n");
	for(i = 1; i<n; i++){
		printf(" %c | ", str2[i-1]);
		for(j = 1; j<m; j++){
			printf("%d | ", memo[i][j]);
		}
		printf("\n");
	}
	
	printf("\n[+] LCS: ");
	for(i=k;i>=0;i--)
		printf("%c", lcs[i]);

	printf("\n");
	return 0;
}

/*

Input1:
4
abcd
2
bd

Input2:
7
longest
5
stone

Input3:
6
abdace
5
babce

*/
