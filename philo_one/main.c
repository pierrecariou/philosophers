/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:18:37 by pcariou           #+#    #+#             */
/*   Updated: 2021/02/07 01:32:26 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_one.h"

void	free_all(t_options *opt, pthread_t *philo)
{
	int	i;

	i = 0;
	free(philo);
	while (i < opt->philo_n + 1)
		pthread_mutex_destroy(&opt->locks[i++]);
	free(opt->locks);
	free(opt);
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
		pthread_create(&philo[i], NULL, philosopher, opt);
	while (g_alive)
		usleep(1);
	free_all(opt, philo);
}

int		error_msgs(int argc, char **argv)
{
	if (argc != 5)
	{
		printf("Invalid number of arguments\n");
		return (2);
	}
	if (!is_num(argc, argv))
	{
		printf("Invalid type of argument\n");
		return (3);
	}
	if (ft_atoi(argv[1]) <= 1)
	{
		printf("You must have at least two philosophers\n");
		return (3);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_options	*opt;
	int			i;
	int			error_code;

	i = 0;
	if ((error_code = error_msgs(argc, argv)) != 0)
		return (error_code);
	opt = malloc(sizeof(t_options));
	if (!opt)
		return (1);
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
