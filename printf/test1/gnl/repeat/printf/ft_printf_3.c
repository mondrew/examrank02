/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 00:02:30 by mondrew           #+#    #+#             */
/*   Updated: 2020/08/06 00:06:58 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

int		ft_printf(char *fmt, ...)
{
	va_list ap;
	int		num;

	num = 0;
	va_start(ap, fmt);
	while (*fmt != '\0')
	{
		if (*fmt == '%')
		{
			fmt++;
			if (*fmt == '%')
			{
				write(1, fmt, 1);
				num++;
			}
			else
			{
				if (!(ft_parse_str(&ap, fmt, &num)))
				{
					va_end(ap);
					return (0);
				}
				while (*fmt != 'd' && *fmt != 's' && *fmt != 'x' && *fmt != '\0')
					fmt++;
			}
		}
		else
		{
			write(1, fmt, 1);
			num++;
		}
		fmt++;
	}
	va_end(ap);
	return (num);
}
