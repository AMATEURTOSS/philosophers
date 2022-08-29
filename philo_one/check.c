/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:22:15 by yochoi            #+#    #+#             */
/*   Updated: 2021/02/02 18:51:04 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	print_death(int time, int i)
{
	pthread_mutex_lock(&g_print);
	ft_putnbr(time);
	ft_putchar(' ');
	ft_putstr("philosopher ");
	ft_putnbr(i);
	ft_putstr(": ");
	ft_putstr("\x1B[31mis dead\x1B[0m");
	ft_putchar('\n');
	pthread_mutex_unlock(&g_print);
}

void		*health_check(void *vphilo)
{
	t_philo *philo;

	philo = vphilo;
	while (1)
	{
		if (philo->is_dead == true || g_finish == true)
			return (NULL);
		if ((current_time()) - philo->last_eat >= g_info.time_to_die)
		{
			philo->is_dead = true;
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_lock(&g_access_finish);
			g_finish = true;
			pthread_mutex_unlock(&g_access_finish);
			print_death(current_time(), philo->i);
			return (NULL);
		}
		if (philo->is_dead == true || g_finish == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

void		*must_eat_check(void *vptr)
{
	int		i;
	bool	finish;

	(void)vptr;
	usleep(100);
	while (1)
	{
		i = 0;
		finish = true;
		while (i < g_info.num_of_philos)
		{
			if (g_philos[i].all_eat == false)
				finish = false;
			++i;
		}
		if (finish)
		{
			pthread_mutex_lock(&g_access_finish);
			g_finish = true;
			pthread_mutex_unlock(&g_access_finish);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}
