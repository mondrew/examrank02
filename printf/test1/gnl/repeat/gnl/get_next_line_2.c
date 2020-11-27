/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 19:51:21 by mondrew           #+#    #+#             */
/*   Updated: 2020/08/05 21:31:39 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	if (!(new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
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
	(*line) = '\0';
	free(*str);
	return (1);
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
		free(*str);
		free(*line);
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

int		get_next_line(char **line)
{
	static char	*str;
	static int	time = 0;
	int			ret;
	char		buf[BUFFER_SIZE + 1];

	if (time == 0)
	{
		if (!(str = ft_strjoin("", "")))
			return (-1);
		time++;
	}
	while (1)
	{
		if ((ret = read(0, buf, BUFFER_SIZE)) < 0)
		{
			free(str);
			return (-1);
		}
		if (ret == 0)
		{
			if (!(ft_finish(&str, line)))
				return (-1);
			return (0);
		}
		buf[ret] = '\0';
		if (!(str = ft_strjoin_free(str, buf)))
			return (-1);
		if ((ft_check_newline(str)) != 0)
		{
			if (!(ft_push_line(&str, line)))
				return (-1);
			break;
		}
	}
	return (1);
}
