/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 19:49:41 by mondrew           #+#    #+#             */
/*   Updated: 2020/08/06 09:28:30 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

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
	while (i < 8)
	{
		n = (bin[j] - 48) * 8 + (bin[j + 1] - 48) * 4 + \
				 (bin[j + 2] - 48) * 2 + (bin[j + 3] - 48);
		if (n > 9)
			hex[i] = 'a' + (n - 10);
		else
			hex[i] = n + 48;
		j += 4;
		i++;
	}
	hex[i] = '\0';
	i = 0;
	n = 0;
	while (hex[i] == '0')
		i++;
	if (i != 0)
	{
		while (hex[n] != '\0')
		{
			hex[n] = hex[i];
			n++;
			i++;
		}
	}
	return (hex);
}

void	ft_neg_to_pos(char *bin)
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
	i = 31;
	if (bin[i] == '0')
		bin[i] = '1';
	else
	{
		bin[i] = '0';
		i--;
		while (i > 0 && bin[i] == '1')
		{
			bin[i] = '0';
			i--;
		}
		bin[i] = '1';
	}
}

char	*ft_min_neg(char *str)
{
	int i;

	i = 1;
	str[0] = '1';
	while (i < 33)
	{
		str[i] = '0';
		i++;
	}
	return (str);
}

char	*ft_dec_to_bin(int dec)
{
	char	*bin;
	int		neg_flag;
	int		i;

	i = 32;
	neg_flag = 0;
	if (!(bin = malloc(sizeof(char) * 33)))
		return (NULL);
	if (dec < 0)
	{
		if (dec == -2147483648)
			return(ft_min_neg(bin)); 
		dec = -dec;
		neg_flag = 1;
	}
	bin[i] = '\0';
	i--;
	while (dec != 0)
	{
		bin[i] = dec % 2 + '0';
		dec = dec / 2;
		i--;
	}
	while (i >= 0)
		bin[i--] = '0';
	if (neg_flag == 1)
		ft_neg_to_pos(bin);
	return (bin);
}

char	*ft_itoh(int dec)
{
	char	*bin;
	char	*hex;

	if (!(bin = ft_dec_to_bin(dec)))
		return (NULL);
	if (!(hex = ft_bin_to_hex(bin)))
	{
		free(bin);
		return (NULL);
	}
	free(bin);
	return (hex);
}

int		ft_atoi(const char *str)
{
	int num;
	int	sign;

	num = 0;
	sign = 1;
	while (*str == ' ' || *str == '\f' || *str == '\n' || *str == '\r' || \
			*str == '\t' || *str == '\v')
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

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		tmp;
	int		neg_flag;

	neg_flag = 1;
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
		neg_flag = -1;
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
	str[len] = '\0';
	len--;
	while (n > 9)
	{
		str[len] = n % 10 + '0';
		len--;
		n = n / 10;
	}
	str[len] = n + '0';
	if (neg_flag == -1)
		str[0] = '-';
	return (str);
}

char	*ft_check_precision_hex(char *str, int str_len, int precision)
{
	int		null;
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	null = precision - str_len;
	if (null <= 0)
		return (str);
	if (!(new = malloc(sizeof(char) * (str_len + null + 1))))
	{
		free(str);
		return (NULL);
	}
	while (null > 0)
	{
		new[i] = '0';
		null--;
		i++;
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

char	*ft_check_precision(char *str, int str_len, int precision, int n)
{
	int		null;
	int		sign;
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	sign = 0;
	if (n < 0)
		sign = 1;
	null = precision - (str_len - sign);
	if (null <= 0)
		return (str);
	if (!(new = malloc(sizeof(char) * (str_len + null + 1))))
	{
		free(str);
		return (NULL);
	}
	if (n < 0)
	{
		new[i] = '-';
		i++;
		j++;////////!!!!!!
	}
	while (null > 0)
	{
		new[i] = '0';
		null--;
		i++;
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

int		ft_print_hex(va_list *ap, int precision, int mfw, int *num)
{
	int		n;
	char	*str;
	int		str_len;

	n = va_arg(*ap, int);
	if (!(str = ft_itoh(n)))
		return (0);
	str_len = ft_strlen(str);
	if (precision > 0)
	{
		if (!(str = ft_check_precision_hex(str, str_len, precision)))
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
	*num += str_len;
	free(str);
	return (1);
}

int		ft_print_decimal(va_list *ap, int precision, int mfw, int *num)
{
	int		n;
	char	*str;
	int		str_len;

	n = va_arg(*ap, int);
	if (!(str = ft_itoa(n)))
		return (0);
	str_len = ft_strlen(str);
	if (precision > 0)
	{
		if (!(str = ft_check_precision(str, str_len, precision, n)))
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
	*num += str_len;
	free(str);
	return (1);
}

void	ft_print_string(va_list *ap, int precision, int mfw, int *num)
{
	char	*str;
	int		str_len;

	str = va_arg(*ap, char *);
	str_len = ft_strlen(str);
	if (precision > 0 && precision < str_len)
		str_len = precision;
	while (mfw > str_len)
	{
		write(1, " ", 1);
		mfw--;
		(*num)++;
	}
	write(1, str, str_len);
	*num += str_len;
}

int		ft_parse_str(const char *fmt, va_list *ap, int *num)
{
	int precision;
	int mfw;

	mfw = 0;
	precision = 0;
	while (*fmt != 'd' && *fmt != 's' && *fmt != 'x' && *fmt != '\0')
	{
		if (*fmt >= '0' && *fmt <= '9')
		{
			mfw = ft_atoi(fmt);
			while (*fmt >= '0' && *fmt <= '9')
				fmt++;
		}
		if (*fmt == '.')
		{
			fmt++;
			precision = ft_atoi(fmt);
			while (*fmt >= '0' && *fmt <= '9')
				fmt++;
		}
	}
	if (*fmt == 's')
		ft_print_string(ap, precision, mfw, num);
	else if (*fmt == 'd')
	{
		if (!(ft_print_decimal(ap, precision, mfw, num)))
			return (0);
	}
	else if (*fmt == 'x')
	{
		if (!(ft_print_hex(ap, precision, mfw, num)))
			return (0);
	}
	return (1);
}

int		ft_printf(const char *format, ...)
{
	va_list ap;
	int		num;

	num = 0;
	va_start(ap, format);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			if (*format == '%')
			{
				write(1, format, 1);
				num++;
			}
			else
			{
				if (!(ft_parse_str(format, &ap, &num)))
					return (0);
				while (*format != 'd' && *format != 's' && *format != 'x')
					format++;
			}
		}
		else
		{
			write(1, format, 1);
			num++;
		}
		format++;
	}
	va_end(ap);
	return (num);
}

int		main(void)
{
	int a = printf("Hello, World!\nDEC: %10.5d\nSTR: %10.5s\nHEX: %10.5x\n", 765, "This is string", 765);
	int b = ft_printf("Hello, World!\nDEC: %10.5d\nSTR: %10.5s\nHEX: %10.5x\n", 765, "This is string", 765);
	printf("orig: %d\nmy--: %d\n", a, b);
	return (0);
}
