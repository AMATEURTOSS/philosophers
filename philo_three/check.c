/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:22:15 by yochoi            #+#    #+#             */
/*   Updated: 2021/02/02 19:27:42 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	print_death(int time, int i)
{
	sem_wait(g_print);
	ft_putnbr(time);
	ft_putchar(' ');
	ft_putstr("philosopher ");
	ft_putnbr(i);
	ft_putstr(": ");
	ft_putstr("\x1B[31mis dead\x1B[0m");
	ft_putchar('\n');
	sem_post(g_print);
}

void		*health_check(void *vphilo)
{
	t_philo *philo;

	philo = vphilo;
	while (1)
	{
		if ((current_time()) - philo->last_eat >= g_info.time_to_die)
		{
			philo->is_dead = true;
			print_death(current_time(), philo->i);
			my_exit(philo, 0);
		}
		usleep(1000);
	}
	return (NULL);
}
