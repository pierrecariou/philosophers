/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die_in_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 13:11:23 by pcariou           #+#    #+#             */
/*   Updated: 2021/02/10 23:28:47 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_one.h"

void	die_while_eating(struct timeval *tv, int id, t_options *opt)
{
	if (opt->time_d < (opt->time_e / 1000))
	{
		if (g_alive)
			usleep(opt->time_d * 1000);
		sem_wait(opt->sem_sent);
		gettimeofday(&tv[1], NULL);
		if (g_alive)
			printf("%ld %d died\n", (tv[1].tv_sec * 1000) +
			(tv[1].tv_usec / 1000), id);
		g_alive = 0;
		sem_post(opt->sem_sent);
	}
}

void	die_in_action(struct timeval *tv, int id, t_options *opt, int time_a)
{
	if (((tv[1].tv_sec * 1000) + (tv[1].tv_usec / 1000) + (time_a / 1000)) -
			((tv[0].tv_sec * 1000) + (tv[0].tv_usec / 1000)) > opt->time_d)
	{
		if (g_alive)
			usleep((opt->time_d * 1000) - ((((tv[1].tv_sec * 1000) +
			(tv[1].tv_usec / 1000)) * 1000) - (((tv[0].tv_sec * 1000) +
			(tv[0].tv_usec / 1000)) * 1000)));
		sem_wait(opt->sem_sent);
		gettimeofday(&tv[1], NULL);
		if (g_alive)
			printf("%ld %d died\n", (tv[1].tv_sec * 1000) +
			(tv[1].tv_usec / 1000), id);
		g_alive = 0;
		sem_post(opt->sem_sent);
	}
}

void	eating(struct timeval *tv, int id, t_options *opt)
{
	if (g_alive)
		printf("%ld %d is eating\n", (tv[0].tv_sec * 1000)
		+ (tv[0].tv_usec / 1000), id);
	sem_post(opt->sem_sent);
	die_while_eating(tv, id, opt);
	if (g_alive)
		usleep(opt->time_e);
}

int		nme(t_options *opt, int id)
{
	if (opt->is_nme)
	{
		opt->nme[id - 1]--;
		if (!opt->nme[id - 1])
			return (1);
	}
	return (0);
}
