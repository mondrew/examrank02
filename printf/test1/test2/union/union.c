#include <unistd.h>

void	ft_union(char *s1, char *s2)
{
	int		i;
	int		j;

	i = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		while (j < i)
		{
			if (s1[j] == s1[i])
				break ;
			j++;
		}
		if (j == i)
			write(1, &(s1[i]), 1);
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		j = 0;
		while (s1[j] != '\0')
		{
			if (s1[j] == s2[i])
				break ;
			j++;
		}
		if (s1[j] == '\0')
		{
			j = 0;
			while (j < i)
			{
				if (s2[j] == s2[i])
					break;
				j++;
			}
			if (j == i)
				write(1, &(s2[i]), 1);
		}
		i++;
	}
}

int		main(int argc, char **argv)
{
	if (argc != 3)
	{
		write(1, "\n", 1);
		return (0);
	}
	ft_union(argv[1], argv[2]);
	write(1, "\n", 1);
	return (0);
}
