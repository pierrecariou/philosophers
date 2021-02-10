/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 01:32:35 by pcariou           #+#    #+#             */
/*   Updated: 2021/02/11 00:09:23 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_one.h"

void	dead_or_alive(struct timeval tv, struct timeval tvb,
		int id, t_options *opt)
{
	int i;

	i = -1;
	if (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) -
			((tvb.tv_sec * 1000) + (tvb.tv_usec / 1000)) > opt->time_d)
	{
		sem_wait(opt->sem_sent);
		printf("%ld %d died\n", (tv.tv_sec * 1000) + (tv.tv_usec / 1000), id);
		while (++i < opt->philo_n)
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
	die_while_eating(tv, id, opt);
	usleep(opt->time_e);
	sem_post(opt->sem);
	sem_post(opt->sem);
	nme(opt, id);
	action(tv, id, opt, "is sleeping");
	die_in_action(tv, id, opt, opt->time_s);
	usleep(opt->time_s);
	action(tv, id, opt, "is thinking");
	die_in_action(tv, id, opt, opt->time_s / 100);
	usleep(opt->time_s / 100);
	gettimeofday(&tv[1], NULL);
	dead_or_alive(tv[1], tv[0], id, opt);
}

void	philosopher(t_options *opt, int id)
{
	struct timeval	tv[2];

	gettimeofday(&tv[0], NULL);
	while (1)
		actions(tv, id, opt);
	exit(0);
}
