/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 01:32:35 by pcariou           #+#    #+#             */
/*   Updated: 2021/02/09 18:35:51 by pcariou          ###   ########.fr       */
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
		if (g_alive)
			printf("%ld %d died\n", (tv.tv_sec * 1000) +
			(tv.tv_usec / 1000), id);
		g_alive = 0;
		sem_post(opt->sem_sent);
	}
}

void	action(struct timeval *tv, int id, t_options *opt, char *str)
{
	gettimeofday(&tv[1], NULL);
	dead_or_alive(tv[1], tv[0], id, opt);
	sem_wait(opt->sem_sent);
	if (g_alive)
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
	if (g_alive)
		printf("%ld %d is eating\n", (tv[0].tv_sec * 1000)
		+ (tv[0].tv_usec / 1000), id);
	sem_post(opt->sem_sent);
	die_while_eating(tv, id, opt);
	if (g_alive)
		usleep(opt->time_e);
	sem_post(opt->sem);
	sem_post(opt->sem);
	action(tv, id, opt, "is sleeping");
	die_in_action(tv, id, opt, opt->time_s);
	if (g_alive)
		usleep(opt->time_s);
	action(tv, id, opt, "is thinking");
	die_in_action(tv, id, opt, opt->time_s / 100);
	if (g_alive)
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
	gettimeofday(&tv[0], NULL);
	while (g_alive)
		actions(tv, id, opt);
	return (NULL);
}
