/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 23:56:37 by mondrew           #+#    #+#             */
/*   Updated: 2020/08/06 11:06:13 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

char	*bin_to_hex(char *bin)
{
	char	*hex;
	int		i;
	int		j;
	int		n;

	i = 0;
	j = 0;
	n = 0;
	if (!(hex = malloc(sizeof(char) * 9)))
		return (NULL);
	hex[8] = '\0';
	while (i < 8)
	{
		n = (bin[j] - '0') * 8 + (bin[j + 1] - '0') * 4 + \
			(bin[j + 2] - '0') * 2 + (bin[j + 3] - '0');
		if (n > 9)
			hex[i] = 'a' + (n - 10);
		else
			hex[i] = n + '0';
		i++;
		j += 4;
	}
	i = 0;
	j = 0;
	while (hex[i] == '0')
		i++;
	if (i != 0)
	{
		while (hex[j] != '\0')
		{
			hex[j] = hex[i];
			i++;
			j++;
		}
	}
	return (hex);
}

void	ft_pos_to_neg(char *bin)
{
	int		i;

	i = 0;
	while (bin[i] != '\0')
	{
		if (bin[i] == '1')
			bin[i] = '0';
		else
			bin[i] = '1';
	}
	i--;
	if (bin[i] = '0')
		bin[i] = '1';
	else
	{
		while (bin[i] == '1')
		{
			bin[i] = '0';
			i++;
		}
		bin[i] = '1';
	}
}

char	*ft_dec_to_bin(int n)
{
	char	*bin;
	int		sign;
	int		i;

	i = 31;
	sign = 0;
	if (!(bin = malloc(sizeof(char) * 33)))
		return (NULL);
	bin[32] = '\0';
	if (n < 0)
	{
		if (n == -2147483648)
		{
			bin[i] = '1';
			i++;
			while (i < 32)
			{
				bin[i] = '0';
				i++;
			}
			return (bin);
		}
		n = -n;
		sign = 1;
	}
	while (n > 2)
	{
		bin[i] = n % 2 + '0';
		i++;
		n = n / 2;
	}
	bin[i] = n + '0';
	if (sign != 0)
		ft_pos_to_neg(bin);
	return (bin);
}

char	*itoh(int n)
{
	char	*bin;
	char	*hex;

	if (!(bin = ft_dec_to_bin(int n)))
		return (NULL);
	if (!(hex = ft_bin_to_hex(bin)))
	{
		free(bin);
		return (NULL);
	}
	return (hex);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		neg_flag;
	int		tmp;

	len = 1;
	neg_flag = 0;
	if (n < 0)
	{
		if (n == -2147483648)
		{
			if (!(str = ft_strdup("-2147483648")))
				return (NULL);
			return (str);
		}
		n = -n;
		neg_flag = 1;
		len++;
	}
	tmp = n;
	while (tmp > 9)
	{
		tmp /= 10;
		len++;
	}
	if (n == 0)
		len = 1;
	if (!str = malloc(sizeof(char) * (len + 1)))
		return (NULL);
	if (neg_flag != 0)
		str[0] = '-';
	str[len] = '\0';
	len--;
	while (n > 9)
	{
		str[len] = n % 10 + '0';
		n /= 10;
		len--;
	}
	str[len] = n + '0';
	return (str);
}

char	*ft_check_precision(char *str, int str_len, int prec, int n)
{
	char	*new;
	int		null;
	int		sign;
	int		i;
	int		j;

	i = 0;
	j = 0;
	sign = 0;
	if (n < 0)
		sign = 1;
	null = prec - (str_len - sign);
	if (null <= 0)
		return (str);
	if (!(new = malloc(sizeof(char) * (str_len + null + 1))))
	{
		free(str);
		return (0);
	}
	if (sign != 0)
	{
		new[i] = '-';
		i++;
		j++;
	}
	while (null > 0)
	{
		new[i] = '0';
		i++;
		null--;
	}
	while (str[j] != '\0')
	{
		new[i] = str[j];
		i++;
		j++;
	}
	new[i] = '\0';
	free(str);
	return (new);
}

int		ft_print_decimal(va_list *ap, int mfw, int prec, int *num)
{
	char	*str;
	int		n;
	int		str_len;

	n = va_arg(*ap, int);
	if (!(str = ft_itoa(n)))
		return (0);
	str_len = ft_strlen(str);
	if (prec > 0)
	{
		if (!(str = ft_check_precision(str, str_len, prec, n)))
			return (0);
	}
	str_len = ft_strlen(str);
	while (mfw > 0 && mfw > str_len)
	{
		write(1, " ", 1);
		mfw--;
		(*num)++;
	}
	write(1, str, str_len);
	*num += str_len;
	free(str);
	return (1);
}

void	ft_print_string(va_list *ap, int mfw, int prec, int *num)
{
	char	*str;
	int		str_len;

	str = va_arg(*ap, char *);
	str_len = ft_strlen(str);
	if (prec > 0 && prec < str_len)
		str_len = prec;
	while (mfw > 0 && mfw > str_len)
	{
		write(1, " ", 1);
		mfw--;
		(*num)++;
	}
	write(1, str, str_len);
	*num += str_len;
}

int		ft_parse_str(va_list *ap, char *fmt, int *num)
{
	int		mfw;
	int		prec;

	mfw = 0;
	prec = 0;
	if (*fmt >= '0' && *fmt <= '9')
	{
		mfw = ft_atoi(fmt);
		while (*fmt >= '0' && *fmt <= '9')
			fmt++;
	}
	if (*fmt == '.')
	{
		fmt++;
		if (*fmt >= '0' && *fmt <= '9')
		{
			prec = ft_atoi(fmt);
			while (*fmt >= '0' && *fmt <= '9')
				fmt++;
		}
	}
	if (*fmt == 's')
		ft_print_string(ap, mfw, prec, num);
	else if (*fmt == 'd')
	{
		if (!(ft_print_decimal(ap, mfw, prec, num)))
			return (0);
	}
	else if (*fmt == 'x')
	{
		if (!(ft_print_hex(ap, mfw, prec, num)))
			return (0);
	}
	return (1);
}

int		ft_printf(char *fmt, ...)
{
	va_list	ap;
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
