/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 13:13:45 by mondrew           #+#    #+#             */
/*   Updated: 2020/08/05 15:02:36 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

char	*ft_min_neg_bin(void)
{
	char	*str;
	int		i;

	i = 0;
	if (!(str = malloc(sizeof(char) * 33)))
		return (NULL);
	str[i] = '1';
	i++;
	str[32] = '\0';
	while (i < 32)
	{
		str[i] = '0';
		i++;
	}
	return (str);
}

void	ft_pos_to_neg(char *bin)
{
	int i;

	i = 0;
	while (bin[i] != '\0')
	{
		if (bin[i] == '0')
			bin[i] = '1';
		else
			bin[i] = '0';
		i++;
	}
	i--;
	if (bin[i] == '0')
		bin[i] = '1';
	else
	{
		while (bin[i] == '1')
		{
			bin[i] = '0';
			i--;
		}
		bin[i] = '1';
	}
}

char	*ft_dec_to_bin(int dec)
{
	char	*bin;
	int		i;
	int		neg_flag;

	i = 32;
	neg_flag = 0;
	if (dec < 0)
	{
		if (dec == -2147483648)
			return (ft_min_neg_bin());
		neg_flag = 1;
		dec = -dec;
	}
	if (!(bin = malloc(sizeof(char) * 33)))
		return (NULL);
	bin[i] = '\0';
	i--;
	while (i >= 0)
	{
		bin[i] = dec % 2 + '0';
		dec /= 2;
		i--;
	}
	if (neg_flag != 0)
		ft_pos_to_neg(bin);
	return (bin);
}

char	*ft_bin_to_hex(char *bin)
{
	char	*hex;
	int		i;
	int		j;
	int		n;

	i = 0;
	j = 0;
	if (!(hex = malloc(sizeof(char) * 9)))
		return (NULL);
	while (bin[j] != '\0')
	{
		n = (bin[j] - '0') * 8 + (bin[j + 1] - '0') * 4 + \
				 (bin[j + 2] - '0') * 2 + (bin[j + 3] - '0') * 1;
		if (n > 9)
			hex[i] = 'a' + (n - 10);
		else
			hex[i] = n + '0';
		i++;
		j += 4;
	}
	hex[i] = '\0';
	i = 0;
	n = 0;
	while (hex[i] == '0')
		i++;
	while (hex[n] != '\0')
	{
		hex[n] = hex[i];
		i++;
		n++;
	}
	return (hex);
}

char	*ft_itoh(int dec)
{
	char	*bin;
	char	*hex;

	if (!(bin = ft_dec_to_bin(dec)))
		return (NULL);
	if (!(hex = ft_bin_to_hex(bin)))
		return (NULL);
	return (hex);
}

int		ft_atoi(char *str)
{
	int num;
	int sign;

	sign = 1;
	num = 0;
	while (*str == '\n' || *str == '\v' || *str == '\t' || \
			*str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + *str - '0';
		str++;
	}
	return (num * sign);
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	char	*new;
	int		i;

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

char	*ft_itoa(int n)
{
	char	*str;
	int		sign;
	int		len;
	int		tmp;

	sign = 0;
	len = 1;
	if (n < 0)
	{
		if (n == -2147483648)
		{
			if (!(str = ft_strdup("-2147483648")))
				return (NULL);
			return (str);
		}
		n = -n;
		sign = 1;
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
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (sign != 0)
		str[0] = '-';
	str[len] = '\0';
	len--;
	while (n > 9)
	{
		str[len] = n % 10 + '0';
		n = n / 10;
		len--;
	}
	str[len] = n + '0';
	return (str);
}

char	*ft_check_precision_hex(char *str, int str_len, int prec)
{
	char	*new;
	int		null;
	int		i;
	int		j;

	i = 0;
	j = 0;
	null = 0;
	null = prec - str_len;
	if (null <= 0)
		return (str);
	if (!(new = malloc(sizeof(char) * (str_len + null + 1))))
	{
		free(str);
		return (0);
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

char	*ft_check_precision(char *str, int str_len, int prec, int n)
{
	char	*new;
	int		null;
	int		sign;
	int		i;
	int		j;

	i = 0;
	j = 0;
	null = 0;
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
	if (n < 0) ////////////////////// check in original
	{
		new[i] = '-';
		i++;
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

int		ft_print_hex(va_list *ap, int prec, int mfw, int *num)
{
	int 	n;
	char	*str;
	int		str_len;

	n = va_arg(*ap, int);
	if (!(str = ft_itoh(n)))
		return (0);
	str_len = ft_strlen(str);
	if (prec > 0)
	{
		if (!(str = ft_check_precision_hex(str, str_len, prec)))
			return (0);
	}
	str_len = ft_strlen(str);
	while (mfw > str_len)
	{
		write(1, " ", 1);
		mfw--;
		(*num)++;
	}
	write(1, str, str_len);
	(*num) += str_len;
	free(str);
	return (1);
}

int		ft_print_decimal(va_list *ap, int prec, int mfw, int *num)
{
	int 	n;
	char	*str;
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
	while (mfw > str_len)
	{
		write(1, " ", 1);
		mfw--;
		(*num)++;
	}
	write(1, str, str_len);
	(*num) += str_len;
	free(str);
	return (1);
}

void	ft_print_string(va_list *ap, int prec, int mfw, int *num)
{
	char	*str;
	int		str_len;

	str_len = 0;
	str = va_arg(*ap, char *);
	str_len = ft_strlen(str);
	if (prec > 0 && prec < str_len)
		str_len = prec;
	while (mfw > str_len)
	{
		write(1, " ", 1);
		(*num)++;
		mfw--;
	}
	write(1, str, str_len);
	(*num) += str_len;
}

int		ft_parse_str(va_list *ap, char *fmt, int *num)
{
	int prec;
	int mfw;

	prec = 0;
	mfw = 0;
	if (*fmt >= '0' && *fmt <= '9')
	{
		mfw = ft_atoi(fmt);
		while (*fmt >= '0' && *fmt <= '9')
			fmt++;
	}
	if (*fmt == '.')
	{
		fmt++;
		prec = ft_atoi(fmt);
		while (*fmt >= '0' && *fmt <= '9')
			fmt++;
	}
	if (*fmt == 's')
		ft_print_string(ap, prec, mfw, num);
	else if (*fmt == 'd')
	{
		if (!(ft_print_decimal(ap, prec, mfw, num)))
			return (0);
	}
	else if (*fmt == 'x')
	{
		if (!(ft_print_hex(ap, prec, mfw, num)))
			return (0);
	}
	return (1);
}

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
					return (0);
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
