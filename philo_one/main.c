/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:18:37 by pcariou           #+#    #+#             */
/*   Updated: 2021/02/05 20:33:11 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_one.h"

void	*test(void *arg)
{
	t_options	*opt;
	int			*alive;
	int			id;
	struct		timeval tv;
	struct		timeval tvb;
	int 		f1;
	int 		f2;
	int 		fcp;
	int			forks;

	alive = malloc(sizeof(int));
	*alive = 1;
	opt = (t_options *)arg;
	pthread_mutex_lock(&g_lock);
	id = g_id++;
	pthread_mutex_unlock(&g_lock);
	f1 = id - 1;
	f2 = (id == opt->philo_n) ? 0 : id + 1;
	forks = 0;
	if (id % 2)
	{
		fcp = f1;
		f1 = f2;
		f2 = fcp;
	}
	gettimeofday(&tvb, NULL);
	while (*alive == 1)
	{
		if (g_forks[f1])
		{
			pthread_mutex_lock(&g_lock);
			g_forks[f1] = 0;
			pthread_mutex_unlock(&g_lock);
			gettimeofday(&tv, NULL);
			printf("%ld %d has taken a fork\n", (tv.tv_sec * 1000) + (tv.tv_usec / 1000) , id);
			forks++;
		}
		if (g_forks[f2])
		{
			pthread_mutex_lock(&g_lock);
			g_forks[f2] = 0;
			pthread_mutex_unlock(&g_lock);
			gettimeofday(&tv, NULL);
			printf("%ld %d has taken a fork\n", (tv.tv_sec * 1000) + (tv.tv_usec / 1000) , id);
			forks++;
		}
		if (forks == 2)
		{
			forks = 0;
			gettimeofday(&tvb, NULL);
			printf("%ld %d is eating\n", (tvb.tv_sec * 1000) + (tvb.tv_usec / 1000), id);
			usleep(opt->time_e);
			pthread_mutex_lock(&g_lock);
			g_forks[f1] = 1;
			g_forks[f2] = 1;
			pthread_mutex_unlock(&g_lock);
			gettimeofday(&tv, NULL);
			printf("%ld %d is sleeping\n", (tv.tv_sec * 1000) + (tv.tv_usec / 1000), id);
			usleep(opt->time_s);
			gettimeofday(&tv, NULL);
			printf("%ld %d is thinking\n", (tv.tv_sec * 1000) + (tv.tv_usec / 1000), id);
			//*alive = 0;
		}
		else
			gettimeofday(&tv, NULL);	
		if (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - ((tvb.tv_sec * 1000) + (tvb.tv_usec / 1000)) > opt->time_d)
		{
			//*alive = 0;
			pthread_mutex_lock(&g_lock);
			g_alive = 0;
			printf("%ld %d died\n", (tv.tv_sec * 1000) + (tv.tv_usec / 1000), id);
			//pthread_mutex_unlock(&g_lock);
			//return (alive);
		}
	}
	return (alive);
}

void	create_threads(t_options *opt)
{
	pthread_t	*philo;
	int			i;
	int			*alive;

	alive = malloc(sizeof(int));
	*alive = 1;
	i = -1;
	philo = malloc(sizeof(pthread_t) * opt->philo_n);
	if (!philo)
		return ;
	while (++i < opt->philo_n)
		pthread_create(&philo[i], NULL, test, opt);
	//i = -1;
	//while (++i < opt->philo_n)
	//{
	//	pthread_join(philo[0], (void *)&alive);
	//	if (g_alive ==0)
	//		break ;
	//}
	//printf("test\n");
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
	g_forks = malloc(sizeof(int) * opt->philo_n);
	if (!g_forks)
		return (1);
	while (i < opt->philo_n)
		g_forks[i++] = 1;
	g_id = 1;
	g_alive = 1;
	create_threads(opt);
	return (0);
}
