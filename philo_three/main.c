/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 11:54:26 by yochoi            #+#    #+#             */
/*   Updated: 2021/02/02 19:29:02 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	eat(t_philo *philo)
{
	take_fork(philo);
	print_status(current_time(), philo->i, "has taken a fork", "is eating");
	philo->eat_count += 1;
	my_sleep(g_info.time_to_eat);
	if (g_info.must_eat != -1 && philo->eat_count == g_info.must_eat)
		my_exit(philo, 0);
	philo->last_eat = current_time();
	put_fork_down(philo);
}

void	*philos_life(t_philo *philo)
{
	pthread_t	tid_for_health_check;

	if (philo->i % 2 == 0)
		usleep(1000);
	pthread_create(&tid_for_health_check, NULL, health_check, philo);
	while (1)
	{
		eat(philo);
		print_status(current_time(), philo->i, "is sleeping", NULL);
		my_sleep(g_info.time_to_sleep);
		print_status(current_time(), philo->i, "is thinking", NULL);
	}
	pthread_join(tid_for_health_check, NULL);
	my_exit(philo, 0);
}

int		create_philos_and_run(void)
{
	int		i;
	int		status;

	i = -1;
	gettimeofday(&g_tv_start, NULL);
	while (++i < g_info.num_of_philos)
	{
		if ((g_philos[i].pid = fork()) == -1)
			return (1);
		if (g_philos[i].pid == 0)
			philos_life(&g_philos[i]);
	}
	if (g_info.must_eat == -1)
	{
		waitpid(-1, NULL, 0);
		i = -1;
		while (++i < g_info.num_of_philos)
			kill(g_philos[i].pid, SIGINT);
		return (0);
	}
	else
		while ((waitpid(-1, &status, 0)) > 0)
			;
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
	sem_unlink("g_forks");
	sem_unlink("g_print");
	sem_unlink("g_access_finish");
	free(g_philos);
}
