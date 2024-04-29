#include <stdio.h>

int main()
{
	int fd_counter = 0;
	int array[] = {0, 1, 0, 2, 3, 2, 1};
	int size = sizeof(array) / sizeof(array[0]);
	int i = 0;
	while (i < size)
	{
		int unique = 1;
		int j = 0;
		while (j < i)
		{
			if (array[i] == array[j])
			{
				unique = 0;
				break ;
			}
			j++;
		}
		if (unique)
			fd_counter++;
		i++;
	}
	printf("%d\n", fd_counter);
	return (0);
}


