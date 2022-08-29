/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 12:44:53 by yochoi            #+#    #+#             */
/*   Updated: 2021/02/02 19:29:45 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		current_time(void)
{
	int				ret;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	ret = (int)(tv.tv_sec - g_tv_start.tv_sec) * 1000 + \
			(tv.tv_usec - g_tv_start.tv_usec) / 1000;
	return (ret);
}

void	print_status(int time, int i, char *s1, char *s2)
{
	sem_wait(g_print);
	ft_putnbr(time);
	ft_putchar(' ');
	ft_putstr("philosopher ");
	ft_putnbr(i);
	ft_putstr(": ");
	ft_putstr(s1);
	ft_putchar('\n');
	if (s2 != NULL)
	{
		ft_putnbr(time);
		ft_putchar(' ');
		ft_putstr("philosopher ");
		ft_putnbr(i);
		ft_putstr(": ");
		ft_putstr(s2);
		ft_putchar('\n');
	}
	sem_post(g_print);
}

int		error(char *str)
{
	ft_putstr(str);
	return (1);
}

void	my_sleep(int time)
{
	int		sleep_start;

	sleep_start = current_time();
	while (current_time() - sleep_start < time)
	{
	}
}

void	my_exit(t_philo *philo, int status)
{
	put_fork_down(philo);
	exit(status);
}
