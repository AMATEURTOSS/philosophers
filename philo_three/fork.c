/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 15:45:03 by yochoi            #+#    #+#             */
/*   Updated: 2021/02/02 19:28:00 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	take_fork(t_philo *philo)
{
	sem_wait(g_forks);
	sem_wait(g_forks);
	philo->fork_count += 2;
}

void	put_fork_down(t_philo *philo)
{
	while (philo->fork_count)
	{
		sem_post(g_forks);
		philo->fork_count -= 1;
	}
}
