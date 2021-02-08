/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 01:32:35 by pcariou           #+#    #+#             */
/*   Updated: 2021/02/08 13:14:11 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_one.h"

void	dead_or_alive(struct timeval *tv, int id, t_options *opt)
{
	if (((tv[1].tv_sec * 1000) + (tv[1].tv_usec / 1000)) -
			((tv[0].tv_sec * 1000) + (tv[0].tv_usec / 1000)) > opt->time_d)
	{
		pthread_mutex_lock(&opt->locks[opt->philo_n]);
		printf("%ld %d died\n", (tv[1].tv_sec * 1000) +
		(tv[1].tv_usec / 1000), id);
		g_alive = 0;
		while (1)
			usleep(1);
	}
}

void	my_forks(int *f, int id, t_options *opt)
{
	int fcp;

	f[0] = id - 1;
	f[1] = (id == opt->philo_n) ? 0 : id;
	if (id % 2)
	{
		fcp = f[0];
		f[0] = f[1];
		f[1] = fcp;
	}
}

void	action(struct timeval *tv, int id, t_options *opt, char *str)
{
	gettimeofday(&tv[1], NULL);
	dead_or_alive(tv, id, opt);
	pthread_mutex_lock(&opt->locks[opt->philo_n]);
	printf("%ld %d %s\n", (tv[1].tv_sec * 1000) +
	(tv[1].tv_usec / 1000), id, str);
	pthread_mutex_unlock(&opt->locks[opt->philo_n]);
}

void	actions(struct timeval *tv, int id, t_options *opt, int *f)
{
	pthread_mutex_lock(&opt->locks[f[0]]);
	action(tv, id, opt, "has taken a fork");
	pthread_mutex_lock(&opt->locks[f[1]]);
	action(tv, id, opt, "has taken a fork");
	gettimeofday(&tv[0], NULL);
	pthread_mutex_lock(&opt->locks[opt->philo_n]);
	printf("%ld %d is eating\n", (tv[0].tv_sec * 1000)
	+ (tv[0].tv_usec / 1000), id);
	pthread_mutex_unlock(&opt->locks[opt->philo_n]);
	die_while_eating(tv, id, opt);
	usleep(opt->time_e);
	pthread_mutex_unlock(&opt->locks[f[0]]);
	pthread_mutex_unlock(&opt->locks[f[1]]);
	action(tv, id, opt, "is sleeping");
	die_in_action(tv, id, opt, opt->time_s);
	usleep(opt->time_s);
	action(tv, id, opt, "is thinking");
	die_in_action(tv, id, opt, opt->time_s / 100);
	usleep(opt->time_s / 100);
	gettimeofday(&tv[1], NULL);
	dead_or_alive(tv, id, opt);
}

void	*philosopher(void *arg)
{
	t_options		*opt;
	int				id;
	struct timeval	tv[2];
	int				f[2];

	opt = (t_options *)arg;
	pthread_mutex_lock(&opt->locks[0]);
	id = opt->philo_id++;
	pthread_mutex_unlock(&opt->locks[0]);
	my_forks(f, id, opt);
	gettimeofday(&tv[0], NULL);
	while (1)
		actions(tv, id, opt, f);
	return (NULL);
}
