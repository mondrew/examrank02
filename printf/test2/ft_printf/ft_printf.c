#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h> //////////

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

int		ft_atoi(char *str)
{
	int		num;
	int		sign;

	num = 0;
	sign = 1;
	while (*str == '\t' || *str == '\v' || *str == '\r' || \
			*str == '\f' || *str == '\n' || *str == ' ')
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

char	*ft_itoa(int n)
{
	char	*str;
	int		neg_flag;
	int		tmp;
	int		len;

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
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len] = '\0';
	len--;
	if (neg_flag == 1)
		str[0] = '-';
	while (n > 9)
	{
		str[len] = n % 10 + '0';
		n /= 10;
		len--;
	}
	str[len] = n + '0';
	return (str);
}

char	*ft_bin_to_hex(char *bin)
{
	int		i;
	int		j;
	int		n;
	char	*hex;

	i = 0;
	j = 0;
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
	while (hex[j] != '\0')
	{
		hex[j] = hex[j];
		i++;
		j++;
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

char	*ft_dec_to_bin(int n)
{
	char	*bin;
	int		neg_flag;
	int		i;

	i = 31;
	neg_flag = 0;
	if (!(bin = malloc(sizeof(char) * 33)))
		return (NULL);
	bin[32] = '\0';
	if (n < 0)
	{
		if (n == -2147483648)
		{
			i = 0;
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
		neg_flag = 1;
	}
	while (n > 2)
	{
		bin[i] = n % 2 + '0';
		n /= 2;
		i--;
	}
	bin[i] = n + '0';
	i--;
	while (i >= 0)
	{
		bin[i] = '0';
		i--;
	}
	if (neg_flag == 1)
		ft_pos_to_neg(bin);
	return (bin);
}

char	*ft_itoh(int n)
{
	char	*bin;
	char	*hex;

	if (!(bin = ft_dec_to_bin(n)))
		return (NULL);
	if (!(hex = ft_bin_to_hex(bin)))
	{
		free(bin);
		return (NULL);
	}
	free(bin);
	return (hex);
}

char	*ft_check_precision_hex(char *str, int str_len, int prec)
{
	int		null;
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	null = prec - str_len;
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

int		ft_print_hex(va_list *ap, int mfw, int prec, int *num)
{
	int		n;
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
	*num += str_len;
	free(str);
	return (1);
}

char	*ft_check_precision(char *str, int str_len, int prec, int n)
{
	int		sign;
	int		null;
	char	*new;
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
		return (NULL);
	}
	if (sign == 1)
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
	int		n;
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
	*num += str_len;
	free(str);
	return (1);
}

int		ft_print_string(va_list *ap, int mfw, int prec, int *num)
{
	char	*str;
	int		str_len;
	int		null_flag;

	null_flag = 0;
	str = va_arg(*ap, char *);
	if (str == NULL)
	{
		null_flag = 1;
		if (!(str = ft_strdup("(null)")))
			return (0);
	}
	str_len = ft_strlen(str);
	if (prec >= 0 && prec < str_len) ////////////!!!!!!!!!
		str_len = prec;
	while (mfw > str_len)
	{
		write(1, " ", 1);
		mfw--;
		(*num)++;
	}
	write(1, str, str_len);
	*num += str_len;
	if (null_flag == 1)
		free(str);
	return (1);
}

int		ft_parse_str(char *fmt, va_list *ap, int *num)
{
	int		mfw;
	int		prec;

	mfw = 0;
	prec = -1;
	if (*fmt >= '0' && *fmt <= '9')
	{
		mfw = ft_atoi(fmt);
		while (*fmt >= '0' && *fmt <= '9')
			fmt++;
	}
	if (*fmt == '.')
	{
		fmt++;
		prec = 0;
		if (*fmt >= '0' && *fmt <= '9')
		{
			prec = ft_atoi(fmt);
			while (*fmt >= '0' && *fmt <= '9')
				fmt++;
		}
	}
	if (*fmt == 's')
	{
		if (!(ft_print_string(ap, mfw, prec, num)))
			return (0);
	}
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

	va_start(ap, fmt);
	num = 0;
	while (*fmt != '\0')
	{
		if (*fmt == '%')
		{
			fmt++;
			if (*fmt == '%')
			{
				write(1, "%", 1);
				num++;
			}
			else
			{
				if (!(ft_parse_str(fmt, &ap, &num)))
				{
					va_end(ap);
					return (-1);////////
				}
				while (*fmt != 's' && *fmt != 'd' && *fmt != 'x' && *fmt != '\0')
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

int		main(void)
{
	int		a;
	int		b;
	a = printf("Hello, World!\n%%\n%12.3s\n%15.20d\n%5.10x\n", "This is test string", 329874, -21983);
	b = ft_printf("Hello, World!\n%%\n%12.3s\n%15.20d\n%5.10x\n", "This is test string", 329874, -21983);
	printf("orig: %d\nmypf: %d\n", a, b);
	return (0);
}
