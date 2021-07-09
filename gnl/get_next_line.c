#include "get_next_line.h"

int		ft_check_endline(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
	{
		free(s1);
		return (NULL);
	}
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
	free(s1);
	return (new);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

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

int		ft_push_line(char **line, char **str)
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

int		ft_finish(char **str, char **line)
{
	int i;

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
		buf[ret] = '\0';
		if (ret == 0)
		{
			if (!(ft_finish(&str, line)))
				return (-1);
			return (0);
		}
		if (!(str = ft_strjoin_free(str, buf)))
			return (-1);
		if ((ft_check_endline(str)) != 0)
		{
			if (!(ft_push_line(line, &str)))
				return (-1);
			break ;
		}
	}
	return (1);
}

int		main(void)
{
	char	*line;
	int		ret;

	line = NULL;
	while ((ret = get_next_line(&line)) > 0)
	{
		printf("RESULT: %s\n", line);
		free(line);
		line = NULL;
	}
	printf("RESULT: %s\n", line);
	return (0);
}
