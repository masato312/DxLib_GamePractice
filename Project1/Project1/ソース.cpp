#include <stdio.h>

int main(void)

{
	{
		int i, j, a;
		i = 0;
		j = 0;
		a = 0;
		for (i = 0; i < 5; i++) {
			for (j = 0; j < 5 - (i + 1); j++) {
				printf(" ");
			}
			for (a = 0; a < (i + 1) * 2 - 1; a++) {
				printf("*");
			}
			printf("\n");
		}
	}
	{
		int i, j, a;
		i = 0;
		j = 0;
		a = 0;
		for (i = 0; i < 5; i++) {
			for (j = 0; j < i; j++) {
				printf(" ");
			}
			for (a = 0; a < (5 - i) * 2 - 1; a++) {
				printf("*");
			}
			printf("\n");
		}
	}
	int i, j;
	i = 0;
	j = 0;
	for (i = 0; i < 6; i++) {
		for (j = 0; j < i; j++)
		{
			printf("*");
		}
		printf("\n");
	}

	{
		int i, j;
		i = 0;
		j = 0;
		for (i = 0; i < 5; i++) {
			for (j = 5; j > i; j--)
			{
				printf("*");
			}
			printf("\n");
		}
	}

	{
		int i, j, a;
		i = 0;
		j = 0;
		a = 0;
		for (i = 5; i > 0; i--) {
			for (j = 0; j < 6 - i - 1; j++)
			{
				printf(" ");
			}
			for (j = 0; j < i; j++) {
				printf("*");
			}
			printf("\n");
		}
	}
	{
		int i, j, a;
		i = 0;
		j = 0;
		a = 0;
		for (i = 0; i < 6; i++) {
			for (j = 0; j < 6 - i - 1; j++)
			{
				printf(" ");
			}
			for (j = 0; j < i; j++) {
				printf("*");
			}
			printf("\n");
		}
	}
}