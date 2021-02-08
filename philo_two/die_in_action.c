/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die_in_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 13:11:23 by pcariou           #+#    #+#             */
/*   Updated: 2021/02/08 13:18:30 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_one.h"

void	die_while_eating(struct timeval *tv, int id, t_options *opt)
{
	if (opt->time_d < (opt->time_e / 1000))
	{
		usleep(opt->time_d);
		sem_wait(opt->sem_sent);
		gettimeofday(&tv[1], NULL);
		printf("%ld %d died\n", (tv[1].tv_sec * 1000) +
		(tv[1].tv_usec / 1000), id);
		g_alive = 0;
		while (1)
			usleep(1);
	}
}

void	die_in_action(struct timeval *tv, int id, t_options *opt, int time_a)
{
	if (((tv[1].tv_sec * 1000) + (tv[1].tv_usec / 1000) + (time_a / 1000)) -
			((tv[0].tv_sec * 1000) + (tv[0].tv_usec / 1000)) > opt->time_d)
	{
		usleep(opt->time_d - (((tv[1].tv_sec * 1000) + (tv[1].tv_usec / 1000)) -
		((tv[0].tv_sec * 1000) + (tv[0].tv_usec / 1000))));
		sem_wait(opt->sem_sent);
		gettimeofday(&tv[1], NULL);
		printf("%ld %d died\n", (tv[1].tv_sec * 1000) +
		(tv[1].tv_usec / 1000), id);
		g_alive = 0;
		while (1)
			usleep(1);
	}
}
