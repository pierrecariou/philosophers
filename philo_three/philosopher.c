/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 01:32:35 by pcariou           #+#    #+#             */
/*   Updated: 2021/02/08 01:29:00 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_one.h"

void	dead_or_alive(struct timeval tv, struct timeval tvb,
		int id, t_options *opt)
{
	if (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) -
			((tvb.tv_sec * 1000) + (tvb.tv_usec / 1000)) > opt->time_d)
	{
		sem_wait(opt->sem_sent);
		printf("%ld %d died\n", (tv.tv_sec * 1000) + (tv.tv_usec / 1000), id);
		sem_post(opt->sem_died);
		while (1)
			usleep(1);
	}
}

void	action(struct timeval *tv, int id, t_options *opt, char *str)
{
	gettimeofday(&tv[1], NULL);
	dead_or_alive(tv[1], tv[0], id, opt);
	sem_wait(opt->sem_sent);
	printf("%ld %d %s\n", (tv[1].tv_sec * 1000) +
	(tv[1].tv_usec / 1000), id, str);
	sem_post(opt->sem_sent);
}

void	actions(struct timeval *tv, int id, t_options *opt)
{
	sem_wait(opt->sem);
	action(tv, id, opt, "has taken a fork");
	sem_wait(opt->sem);
	action(tv, id, opt, "has taken a fork");
	gettimeofday(&tv[0], NULL);
	sem_wait(opt->sem_sent);
	printf("%ld %d is eating\n", (tv[0].tv_sec * 1000)
	+ (tv[0].tv_usec / 1000), id);
	sem_post(opt->sem_sent);
	usleep(opt->time_e);
	sem_post(opt->sem);
	sem_post(opt->sem);
	action(tv, id, opt, "is sleeping");
	usleep(opt->time_s);
	action(tv, id, opt, "is thinking");
	usleep(opt->time_s / 100);
	gettimeofday(&tv[1], NULL);
	dead_or_alive(tv[1], tv[0], id, opt);
}

void	*philosopher(void *arg)
{
	t_options		*opt;
	int				id;
	struct timeval	tv[2];
	
	opt = (t_options *)arg;
	sem_wait(opt->sem_sent);
	id = opt->philo_id++;
	sem_post(opt->sem_sent);
	opt->pid[id - 1] = fork();
	if (opt->pid[id - 1] == 0)
	{
		gettimeofday(&tv[0], NULL);
		while (1)
			actions(tv, id, opt);
	}
	return (NULL);
}
