/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 11:54:29 by yochoi            #+#    #+#             */
/*   Updated: 2021/02/02 19:25:55 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <string.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>

typedef struct		s_info
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
}					t_info;

typedef struct		s_philo
{
	int				i;
	pid_t			pid;
	int				last_eat;
	int				eat_count;
	bool			is_dead;
	int				fork_count;
}					t_philo;

t_info				g_info;
t_philo				*g_philos;
sem_t				*g_forks;
sem_t				*g_print;
struct timeval		g_tv_start;

/*
** CHECK
*/

void				*health_check(void *vphilo);

/*
** FORK
*/

void				take_fork(t_philo *philo);
void				put_fork_down(t_philo *philo);

/*
** INIT
*/

int					init(int argc, char **argv);

/*
** UTILS
*/

int					ft_strlen(const char *s);
int					ft_atoi(const char *nptr);
void				ft_putchar(char c);
void				ft_putstr(char *s);
void				ft_putnbr(int n);

/*
** UTILS2
*/

int					current_time(void);
void				print_status(int time, int i, char *s1, char *s2);
int					error(char *str);
void				my_sleep(int time);
void				my_exit(t_philo *philo, int status);

#endif
