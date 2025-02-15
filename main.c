#include <unistd.h>
#include <stdio.h>
#include <limits.h>

int ft_abs(int n) { return (n ^ (n >> 31)) - (n >> 31); }


int main()
{
	printf("%d\n", 1 ^ 2);
}

/*
0000001
0000010

0000010

1 + 1 = 0  1
0 + 1 = 1
0 + 0 = 0
1 + 0 = 1
*/
