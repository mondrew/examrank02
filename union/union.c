#include <unistd.h>

void	ft_union2(char *s1, char *s2, int i, int j)
{
	int c;

	while (s2[j] != '\0')
	{
		i = 0;
		while (s1[i] != '\0')
		{
			if (s1[i] == s2[j])
				break ;
			i++;
		}
		if (s1[i] == '\0')
		{
			c = 0;
			while (c < j)
			{
				if (s2[c] == s2[j])
					break ;
				c++;
			}
			if (c == j)
				write(1, &(s2[j]), 1);
		}
		j++;
	}
}

void	ft_union(char *s1, char *s2)
{
	int i;
	int j;
	int c;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		c = 0;
		while (c < i)
		{
			if (s1[c] == s1[i])
				break ;
			c++;
		}
		if (c == i)
			write(1, &(s1[i]), 1);
		i++;
	}
	ft_union2(s1, s2, 0, 0);
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
