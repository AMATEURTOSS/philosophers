/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 11:54:26 by yochoi            #+#    #+#             */
/*   Updated: 2021/02/02 19:23:01 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	print_eat_count(void)
{
	int i;

	i = 0;
	while (i < g_info.num_of_philos)
	{
		ft_putstr("philosoper ");
		ft_putnbr(i);
		ft_putstr(": ");
		ft_putnbr(g_philos[i].eat_count);
		ft_putchar('\n');
		++i;
	}
}

void	eat(t_philo *philo)
{
	sem_wait(g_forks);
	sem_wait(g_forks);
	print_status(current_time(), philo->i, "has taken a fork", "is eating");
	philo->eat_count += 1;
	if (g_info.must_eat != -1 && philo->eat_count == g_info.must_eat)
		philo->all_eat = true;
	my_sleep(g_info.time_to_eat, philo);
	philo->last_eat = current_time();
	sem_post(g_forks);
	sem_post(g_forks);
}

void	*philos_life(void *vptr)
{
	t_philo		*philo;
	pthread_t	tid_for_health_check;

	philo = vptr;
	if (philo->i % 2 == 0)
		usleep(1000);
	pthread_create(&tid_for_health_check, NULL, health_check, philo);
	while (1)
	{
		if (philo->is_dead == true || g_finish == true)
			break ;
		eat(philo);
		print_status(current_time(), philo->i, "is sleeping", NULL);
		my_sleep(g_info.time_to_sleep, philo);
		if (philo->is_dead == true || g_finish == true)
			break ;
		print_status(current_time(), philo->i, "is thinking", NULL);
	}
	pthread_join(tid_for_health_check, NULL);
	return (NULL);
}

int		create_philos_and_run(void)
{
	int			i;
	pthread_t	tid_check_must_eat;

	i = -1;
	gettimeofday(&g_tv_start, NULL);
	if (g_info.must_eat != -1)
	{
		pthread_create(&tid_check_must_eat, NULL, must_eat_check, NULL);
		pthread_detach(tid_check_must_eat);
	}
	while (++i < g_info.num_of_philos)
	{
		if (pthread_create(&g_philos[i].tid, NULL, philos_life, &g_philos[i]) \
				!= 0)
			return (1);
	}
	i = -1;
	while (++i < g_info.num_of_philos)
	{
		pthread_join(g_philos[i].tid, NULL);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (error("Error: argument\n"));
	if (init(argc, argv))
		return (error("Error: init\n"));
	if (create_philos_and_run())
		return (error("Error: error occurred while run\n"));
	print_eat_count();
	sem_unlink("g_forks");
	sem_unlink("g_print");
	sem_unlink("g_access_finish");
	free(g_philos);
}
