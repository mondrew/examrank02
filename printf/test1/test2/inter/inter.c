#include <unistd.h>

void	ft_inter(char *s1, char *s2)
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
		{
			j = 0;
			while (s2[j] != '\0')
			{
				if (s2[j] == s1[i])
				{
					write(1, &(s1[i]), 1);
					break ;
				}
				j++;
			}
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
	ft_inter(argv[1], argv[2]);
	write(1, "\n", 1);
	return (0);
}
