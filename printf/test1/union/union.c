/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 14:47:30 by mondrew           #+#    #+#             */
/*   Updated: 2020/08/05 14:59:11 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_union(char *s1, char *s2)
{
	int i;
	int j;

	i = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		while (j < i)
		{
			if (s1[i] == s1[j])
				break ;
			j++;
		}
		if (i == j)
			write(1, &(s1[i]), 1);
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		j = 0;
		while (s1[j] != '\0')
		{
			if (s2[i] == s1[j])
				break ;
			j++;
		}
		if (s1[j] == '\0')
		{
			j = 0;
			while (j < i)
			{
				if (s2[j] == s2[i])
					break ;
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
