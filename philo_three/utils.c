/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 18:09:16 by yochoi            #+#    #+#             */
/*   Updated: 2021/02/02 19:29:19 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		ft_strlen(const char *s)
{
	int len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

int		ft_atoi(const char *nptr)
{
	int i;
	int result_num;
	int minus;

	i = 0;
	result_num = 0;
	minus = 0;
	while (nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			minus = 1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result_num *= 10;
		result_num += nptr[i] - '0';
		i++;
	}
	return (minus == 0 ? result_num : -result_num);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	write(1, s, ft_strlen(s));
}

void	ft_putnbr(int n)
{
	if (n == -2147483648)
		ft_putstr("-2147483648");
	else if (n < 0)
	{
		ft_putchar('-');
		ft_putnbr(-n);
	}
	else if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putchar(n % 10 + '0');
	}
	else
		ft_putchar(n + '0');
}
