/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 10:38:17 by mondrew           #+#    #+#             */
/*   Updated: 2020/08/13 11:38:58 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#define BUFFER_SIZE 1024
#include <stdio.h> ////////////

int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	char	*new;
	int		i;

	i = 0;
	if (!(new = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	while (str[i] != '\0')
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int		ft_check_newline(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int		ft_push_line(char **str, char **line)
{
	int		i;
	int		j;
	char	*remainder;

	i = 0;
	j = 0;
	while ((*str)[i] != '\n')
		i++;
	if (!(*line = malloc(sizeof(char) * (i + 1))))
	{
		free(*str);
		return (0);
	}
	if (!(remainder = malloc(sizeof(char) * (ft_strlen(*str) - i))))
	{
		free(*line);
		free(*str);
		return (0);
	}
	i = 0;
	while ((*str)[i] != '\n')
	{
		(*line)[i] = (*str)[i];
		i++;
	}
	(*line)[i] = '\0';
	i++;
	while ((*str)[i] != '\0')
	{
		remainder[j] = (*str)[i];
		i++;
		j++;
	}
	remainder[j] = '\0';
	free(*str);
	*str = remainder;
	return (1);
}

int		ft_finish(char **str, char **line)
{
	int		i;

	i = 0;
	if (!(*line = malloc(sizeof(char) * (ft_strlen(*str) + 1))))
	{
		free(*str);
		return (0);
	}
	while ((*str)[i] != '\0')
	{
		(*line)[i] = (*str)[i];
		i++;
	}
	(*line)[i] = '\0';
	free(*str);
	return (1);
}

char	*ft_strjoin_free(char *buf, char *str)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(new = malloc(sizeof(char) * (ft_strlen(buf) + ft_strlen(str) + 1))))
	{
		free(str);
		return (NULL);
	}
	while (str[i] != '\0')
	{
		new[i] = str[i];
		i++;
	}
	while (buf[j] != '\0')
	{
		new[i] = buf[j];
		i++;
		j++;
	}
	new[i] = '\0';
	free(str);
	return (new);
}

int		get_next_line(char **line)
{
	static char	*str;
	static int	start = 0;
	int			ret;
	char		buf[BUFFER_SIZE + 1];

	if (start == 0)
	{
		if (!(str = ft_strdup("")))
			return (-1);
		start++;
	}
	while (1)
	{
		if ((ft_check_newline(str)) == 1)
		{
			if (!(ft_push_line(&str, line)))
				return (-1);
			return (1);
		}
		else
		{
			if ((ret = read(0, buf, BUFFER_SIZE)) < 0)
			{
				free(str);
				return (-1);
			}
			buf[ret] = '\0';
			if (ret == 0)
			{
				if (!(ft_finish(&str, line)))
					return (-1);
				return (0);
			}
			if (!(str = ft_strjoin_free(buf, str)))
				return (-1);
		}
	}
	return (1);
}

int		main(void)
{
	char	*line;

	line = NULL;
	while ((get_next_line(&line)) > 0)
	{
		printf("%s\n", line);
		free(line);
		line = NULL;
	}
	printf("%s\n", line);
	free(line);
	line = NULL;
	return (0);
}
