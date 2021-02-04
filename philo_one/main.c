/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:18:37 by pcariou           #+#    #+#             */
/*   Updated: 2021/02/04 22:02:22 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_one.h"

int		too_late(int b, int c, int max)
{
	if (c - b > max)
		return (1);
	return (0);
}

void	*test(void *arg)
{
	t_options	*opt;
	int			*alive;
	int			id;
	struct		timeval tv;
	struct		timeval tvb;

	alive = malloc(sizeof(int));
	*alive = 1;
	opt = (t_options *)arg;
	id = g_id++;
	gettimeofday(&tvb, NULL);
	while (*alive == 1)
	{
		if (g_forks >= 2)
		{
			gettimeofday(&tv, NULL);
			printf("%ld %d has taken a fork\n", (tv.tv_sec * 1000) + (tv.tv_usec / 1000) , id);
			g_forks -= 2;
			gettimeofday(&tvb, NULL);
			printf("%ld %d is eating\n", (tvb.tv_sec * 1000) + (tvb.tv_usec / 1000), id);
			usleep(opt->time_e);
			g_forks += 2;
			gettimeofday(&tv, NULL);
			printf("%ld %d is sleeping\n", (tv.tv_sec * 1000) + (tv.tv_usec / 1000), id);
			usleep(opt->time_s);
			gettimeofday(&tv, NULL);
			printf("%ld %d is thinking\n", (tv.tv_sec * 1000) + (tv.tv_usec / 1000), id);
			//*alive = 0;
		}
		else
			gettimeofday(&tv, NULL);
		if (too_late((tvb.tv_sec * 1000) + (tvb.tv_usec / 1000), (tv.tv_sec * 1000) + (tv.tv_usec / 1000), opt->time_d))
		{
			*alive = 0;
			printf("%ld %d died\n", (tv.tv_sec * 1000) + (tv.tv_usec / 1000), id);
		}
	}
	return ((void *)alive);
}

void	create_threads(t_options *opt)
{
	pthread_t	*philo;
	int			i;
	int			*alive;

	alive = NULL;
	i = -1;
	philo = malloc(sizeof(pthread_t) * opt->philo_n);
	if (!philo)
		return ;
	while (++i < opt->philo_n)
		pthread_create(&philo[0], NULL, test, opt);
	i = -1;
	while (++i < opt->philo_n)
	{
		pthread_join(philo[0], (void *)&alive);
		printf("%d\n", *alive);
	}
}

int		main(int argc, char **argv)
{
	t_options *opt;

	opt = malloc(sizeof(t_options));
	if (!opt)
		return (1);
	if (argc != 5)
	{
		printf("invalid number of arguments\n");
		return (2);
	}
	if (!is_num(argc, argv))
	{
		printf("invalid type of argument\n");
		return (3);
	}
	opt->philo_n = ft_atoi(argv[1]);
	opt->time_d = ft_atoi(argv[2]) * 1000;
	opt->time_e = ft_atoi(argv[3]) * 1000;
	opt->time_s = ft_atoi(argv[4]) * 1000;
	g_forks = opt->philo_n * 2;
	g_id = 1;
	create_threads(opt);
	return (0);
}
