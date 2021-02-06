/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:18:37 by pcariou           #+#    #+#             */
/*   Updated: 2021/02/06 14:45:05 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_one.h"

void	dead_or_alive(struct timeval tv, struct timeval tvb, int id, t_options *opt)
{
		if (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - ((tvb.tv_sec * 1000) + (tvb.tv_usec / 1000)) > opt->time_d)
		{
			pthread_mutex_lock(&opt->locks[opt->philo_n]);
			printf("%ld %d died\n", (tv.tv_sec * 1000) + (tv.tv_usec / 1000), id);
			g_alive = 0;
			while (1)
				usleep(1);
		}
}

void	*test(void *arg)
{
	t_options	*opt;
	int			id;
	struct		timeval tv;
	struct		timeval tvb;
	int 		f1;
	int 		f2;
	int 		fcp;

	opt = (t_options *)arg;
	pthread_mutex_lock(&opt->locks[0]);
	id = opt->philo_id++;
	pthread_mutex_unlock(&opt->locks[0]);
	f1 = id - 1;
	f2 = (id == opt->philo_n) ? 0 : id;
	if (id % 2)
	{
		fcp = f1;
		f1 = f2;
		f2 = fcp;
	}
	gettimeofday(&tvb, NULL);
	while (1)
	{
		pthread_mutex_lock(&opt->locks[f1]);
		gettimeofday(&tv, NULL);
		dead_or_alive(tv, tvb, id, opt);
		pthread_mutex_lock(&opt->locks[opt->philo_n]);
		printf("%ld %d has taken a fork\n", (tv.tv_sec * 1000) + (tv.tv_usec / 1000) , id);
		pthread_mutex_unlock(&opt->locks[opt->philo_n]);
		pthread_mutex_lock(&opt->locks[f2]);
		gettimeofday(&tv, NULL);
		dead_or_alive(tv, tvb, id, opt);
		pthread_mutex_lock(&opt->locks[opt->philo_n]);
		printf("%ld %d has taken a fork\n", (tv.tv_sec * 1000) + (tv.tv_usec / 1000) , id);
		pthread_mutex_unlock(&opt->locks[opt->philo_n]);
		gettimeofday(&tvb, NULL);
		pthread_mutex_lock(&opt->locks[opt->philo_n]);
		printf("%ld %d is eating\n", (tvb.tv_sec * 1000) + (tvb.tv_usec / 1000), id);
		pthread_mutex_unlock(&opt->locks[opt->philo_n]);
		usleep(opt->time_e);
		pthread_mutex_unlock(&opt->locks[f1]);
		pthread_mutex_unlock(&opt->locks[f2]);
		gettimeofday(&tv, NULL);
		dead_or_alive(tv, tvb, id, opt);
		pthread_mutex_lock(&opt->locks[opt->philo_n]);
		printf("%ld %d is sleeping\n", (tv.tv_sec * 1000) + (tv.tv_usec / 1000), id);
		pthread_mutex_unlock(&opt->locks[opt->philo_n]);
		usleep(opt->time_s);
		gettimeofday(&tv, NULL);
		dead_or_alive(tv, tvb, id, opt);
		pthread_mutex_lock(&opt->locks[opt->philo_n]);
		printf("%ld %d is thinking\n", (tv.tv_sec * 1000) + (tv.tv_usec / 1000), id);
		pthread_mutex_unlock(&opt->locks[opt->philo_n]);
		usleep(opt->time_s / 100);
		gettimeofday(&tv, NULL);
		dead_or_alive(tv, tvb, id, opt);
	}
	return (NULL);
}

void	create_threads(t_options *opt)
{
	pthread_t	*philo;
	int			i;

	i = -1;
	philo = malloc(sizeof(pthread_t) * opt->philo_n);
	if (!philo)
		return ;
	while (++i < opt->philo_n)
		pthread_create(&philo[i], NULL, test, opt);
	while (g_alive)
		usleep(1);
}

int		main(int argc, char **argv)
{
	t_options *opt;
	int i;

	i = 0;
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
	opt->time_d = ft_atoi(argv[2]);
	opt->time_e = ft_atoi(argv[3]) * 1000;
	opt->time_s = ft_atoi(argv[4]) * 1000;
	opt->philo_id = 1;
	opt->locks = malloc(sizeof(pthread_mutex_t) * (opt->philo_n + 1));
	if (!opt->locks)
		return (1);
	while (i < opt->philo_n + 1)
		pthread_mutex_init(&opt->locks[i++], NULL);
	g_alive = 1;
	create_threads(opt);
	return (0);
}
