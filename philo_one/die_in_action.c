/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die_in_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 12:21:30 by pcariou           #+#    #+#             */
/*   Updated: 2021/02/09 18:36:37 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_one.h"

void	die_while_eating(struct timeval *tv, int id, t_options *opt)
{
	if (opt->time_d < (opt->time_e / 1000))
	{
		if (g_alive)
			usleep(opt->time_d);
		pthread_mutex_lock(&opt->locks[opt->philo_n]);
		gettimeofday(&tv[1], NULL);
		if (g_alive)
			printf("%ld %d died\n", (tv[1].tv_sec * 1000) +
			(tv[1].tv_usec / 1000), id);
		g_alive = 0;
		pthread_mutex_unlock(&opt->locks[opt->philo_n]);
	}
}

void	die_in_action(struct timeval *tv, int id, t_options *opt, int time_a)
{
	if (((tv[1].tv_sec * 1000) + (tv[1].tv_usec / 1000) + (time_a / 1000)) -
			((tv[0].tv_sec * 1000) + (tv[0].tv_usec / 1000)) > opt->time_d)
	{
		if (g_alive)
			usleep(opt->time_d - (((tv[1].tv_sec * 1000) +
			(tv[1].tv_usec / 1000)) - ((tv[0].tv_sec * 1000) +
			(tv[0].tv_usec / 1000))));
		pthread_mutex_lock(&opt->locks[opt->philo_n]);
		gettimeofday(&tv[1], NULL);
		if (g_alive)
			printf("%ld %d died\n", (tv[1].tv_sec * 1000) +
			(tv[1].tv_usec / 1000), id);
		g_alive = 0;
		pthread_mutex_unlock(&opt->locks[opt->philo_n]);
	}
}
