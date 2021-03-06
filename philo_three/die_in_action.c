/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die_in_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 13:21:42 by pcariou           #+#    #+#             */
/*   Updated: 2021/02/11 00:17:16 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_one.h"

void	die_while_eating(struct timeval *tv, int id, t_options *opt)
{
	int i;

	i = -1;
	if (opt->time_d < (opt->time_e / 1000))
	{
		usleep(opt->time_d * 1000);
		sem_wait(opt->sem_sent);
		gettimeofday(&tv[1], NULL);
		printf("%ld %d died\n", (tv[1].tv_sec * 1000) +
		(tv[1].tv_usec / 1000), id);
		while (++i < opt->philo_n)
			sem_post(opt->sem_died);
		while (1)
			usleep(1);
	}
}

void	die_in_action(struct timeval *tv, int id, t_options *opt, int time_a)
{
	int i;

	i = -1;
	if (((tv[1].tv_sec * 1000) + (tv[1].tv_usec / 1000) + (time_a / 1000)) -
			((tv[0].tv_sec * 1000) + (tv[0].tv_usec / 1000)) > opt->time_d)
	{
		usleep((opt->time_d * 1000) - ((((tv[1].tv_sec * 1000) +
		(tv[1].tv_usec / 1000)) * 1000) - (((tv[0].tv_sec * 1000) +
		(tv[0].tv_usec / 1000)) * 1000)));
		sem_wait(opt->sem_sent);
		gettimeofday(&tv[1], NULL);
		printf("%ld %d died\n", (tv[1].tv_sec * 1000) +
		(tv[1].tv_usec / 1000), id);
		while (++i < opt->philo_n)
			sem_post(opt->sem_died);
		while (1)
			usleep(1);
	}
}

void	nme(t_options *opt, int id)
{
	if (opt->is_nme)
	{
		opt->nme[id - 1]--;
		if (!opt->nme[id - 1])
		{
			sem_post(opt->sem_died);
			exit(0);
		}
	}
}
