#include <stdio.h>
#include<stdlib.h>

/*
  
ind	0 1 2 3 4 5 6
Pat a a b a a b a
LPS 0 1 0 1 2 3 4

abcdabca
00001231

aabaaba
0101234

aabaabaaa
010123452

acacabacacabacacac
001230123456789 10 11 4


12
abxabcabcaby
6
abcaby

8
acacabdc
2
ab

5
abcab
2
ab

*/

void calculateLPS(char *pattern, int *lps, int m){
	int i = 1, j = 0;
	while(i < m)
	{
		while(j>0 && pattern[i]!=pattern[j]){
			j = lps[j-1];
		}
		if (pattern[i] == pattern[j])
		{
			j++;
			lps[i] = j;
		}
		i++;
	}
}

int KMP(char *mainStr, int m, char *pattern, int n, int *lps){
	int pos = -1;
	int i = 0, j = 0;
	while(i < m)
	{
		while(j>0 && mainStr[i]!=pattern[j]){
			j = lps[j-1];
		}
		if (mainStr[i] == pattern[j])
		{
			j++;
		}
		if(j == n){
			pos = i-j+1;
			break;
		}
		i++;
	}
	return pos;
}

int main(void)
{
	char *mainStr, *pattern;
	int mLength, pLength, *lps, i, index;
	printf("Length of main string: ");
	scanf("%d", &mLength);
	
	mainStr = (char*)malloc(mLength+1*sizeof(char));
	
	printf("Main String: ");
	
	getchar();
	fgets(mainStr, mLength+1, stdin);
	
	printf("Length of pattern string: ");
	scanf("%d", &pLength);
	
	pattern = (char*)malloc(pLength+1*sizeof(char));
	printf("Pattern: ");
	
	getchar();
	fgets(pattern, pLength+1, stdin);

	lps = (int *)malloc(pLength*sizeof(int));
	calculateLPS(pattern, lps, pLength);
	index = KMP(mainStr, mLength, pattern, pLength, lps);
	for (i = 0; i < pLength; i++)
	{
		printf("%d | ", lps[i]);
	}
	printf("\n%d", index);
	return 0;
}