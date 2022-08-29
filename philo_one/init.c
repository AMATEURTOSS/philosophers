/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 19:01:21 by yochoi            #+#    #+#             */
/*   Updated: 2021/02/02 18:52:00 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		init_philos(void)
{
	int i;

	i = -1;
	if (!(g_philos = (t_philo *)malloc(sizeof(t_philo) * g_info.num_of_philos)))
		return (1);
	while (++i < g_info.num_of_philos)
	{
		g_philos[i].i = i;
		g_philos[i].left_fork = &g_forkes[i];
		if (i == 0)
			g_philos[i].right_fork = &g_forkes[g_info.num_of_philos - 1];
		else
			g_philos[i].right_fork = &g_forkes[i - 1];
		g_philos[i].last_eat = 0;
		g_philos[i].eat_count = 0;
		g_philos[i].is_dead = false;
		g_philos[i].all_eat = false;
	}
	return (0);
}

int		init_mutex(void)
{
	int i;

	i = -1;
	if (!(g_forkes = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
		* g_info.num_of_philos)))
		return (1);
	while (++i < g_info.num_of_philos)
		pthread_mutex_init(&g_forkes[i], NULL);
	pthread_mutex_init(&g_print, NULL);
	pthread_mutex_init(&g_access_finish, NULL);
	return (0);
}

int		init(int argc, char **argv)
{
	g_info.num_of_philos = ft_atoi(argv[1]);
	g_info.time_to_die = ft_atoi(argv[2]);
	g_info.time_to_eat = ft_atoi(argv[3]);
	g_info.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		g_info.must_eat = ft_atoi(argv[5]);
	else
		g_info.must_eat = -1;
	if (init_mutex())
		return (1);
	if (init_philos())
		return (1);
	return (0);
}
