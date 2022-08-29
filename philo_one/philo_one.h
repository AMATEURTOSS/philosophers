/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 11:54:29 by yochoi            #+#    #+#             */
/*   Updated: 2021/02/02 18:38:39 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <string.h>

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
	pthread_t		tid;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t *right_fork;
	int				last_eat;
	int				eat_count;
	bool			is_dead;
	bool			all_eat;
}					t_philo;

t_info				g_info;
t_philo				*g_philos;
pthread_mutex_t		*g_forkes;
pthread_mutex_t		g_print;
pthread_mutex_t		g_access_finish;
bool				g_finish;
struct timeval		g_tv_start;

/*
** CHECK
*/

void				*health_check(void *vphilo);
void				*must_eat_check(void *vptr);

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
void				my_sleep(int time, t_philo *philo);

#endif
