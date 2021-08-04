#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char mainStr[100], pattern[10];
	int mLength, pLength, i, j, flag=1;
	printf("Main String: ");
	fgets(mainStr, 100, stdin);
	printf("Pattern: ");
	fgets(pattern, 10, stdin);
	mLength = strlen(mainStr)-1;
	pLength = strlen(pattern)-1;
	
	// printf("%s", mainStr);
	// printf("len: %d\n", mLength);
	// printf("%s", pattern);
	// printf("len: %d\n", pLength);
	
	for (i = 0; i <= mLength-pLength; i++)
	{
		for (j = 0; j < pLength; j++)
		{
			if (mainStr[i+j]!=pattern[j])
				break;
		}
		if (j == pLength)
		{
			printf("Found @ pos:%d\n", i);
			flag = 0;
			break;
		}
	}
	if (flag)
	{
		printf("Not Found!\n");
	}
	return 0;
}