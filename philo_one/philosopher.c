/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 01:32:35 by pcariou           #+#    #+#             */
/*   Updated: 2021/02/10 20:51:33 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_one.h"

void	dead_or_alive(struct timeval *tv, int id, t_options *opt)
{
	if (((tv[1].tv_sec * 1000) + (tv[1].tv_usec / 1000)) -
			((tv[0].tv_sec * 1000) + (tv[0].tv_usec / 1000)) > opt->time_d)
	{
		pthread_mutex_lock(&opt->locks[opt->philo_n]);
		if (g_alive)
			printf("%ld %d died\n", (tv[1].tv_sec * 1000) +
			(tv[1].tv_usec / 1000), id);
		g_alive = 0;
		pthread_mutex_unlock(&opt->locks[opt->philo_n]);
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
	if (g_alive)
		printf("%ld %d %s\n", (tv[1].tv_sec * 1000) +
		(tv[1].tv_usec / 1000), id, str);
	pthread_mutex_unlock(&opt->locks[opt->philo_n]);
}

int		actions(struct timeval *tv, int id, t_options *opt, int *f)
{
	pthread_mutex_lock(&opt->locks[f[0]]);
	action(tv, id, opt, "has taken a fork");
	pthread_mutex_lock(&opt->locks[f[1]]);
	action(tv, id, opt, "has taken a fork");
	gettimeofday(&tv[0], NULL);
	pthread_mutex_lock(&opt->locks[opt->philo_n]);
	eating(tv, id, opt);
	pthread_mutex_unlock(&opt->locks[f[0]]);
	pthread_mutex_unlock(&opt->locks[f[1]]);
	if (nme(opt, id))
		return (1);
	action(tv, id, opt, "is sleeping");
	die_in_action(tv, id, opt, opt->time_s);
	if (g_alive)
		usleep(opt->time_s);
	action(tv, id, opt, "is thinking");
	die_in_action(tv, id, opt, opt->time_s / 100);
	if (g_alive)
		usleep(opt->time_s / 100);
	gettimeofday(&tv[1], NULL);
	dead_or_alive(tv, id, opt);
	return (0);
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
	while (g_alive)
	{
		if (actions(tv, id, opt, f))
			break ;
	}
	return (NULL);
}
