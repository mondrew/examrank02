#include <unistd.h>

void	ft_inter(char *s1, char *s2)
{
	int i;
	int j;
	int	c;

	i = 0;
	while (s1[i] != '\0')
	{
		c = 0;
		j = 0;
		while (c < i)
		{
			if (s1[i] == s1[c])
				break ;
			c++;
		}
		if (c == i)
		{
			while (s2[j] != '\0' && s1[i] != s2[j])
				j++;
			if (s2[j] != '\0')
				write(1, &(s1[i]), 1);
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
