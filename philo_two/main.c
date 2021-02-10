/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:18:37 by pcariou           #+#    #+#             */
/*   Updated: 2021/02/11 00:15:25 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_one.h"

void	free_all(t_options *opt, pthread_t *philo)
{
	free(philo);
	sem_close(opt->sem);
	sem_close(opt->sem_sent);
	if (opt->is_nme)
		free(opt->nme);
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
	i = -1;
	while (++i < opt->philo_n)
		pthread_join(philo[i], NULL);
	free_all(opt, philo);
}

int		error_msgs(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Invalid number of arguments\n");
		return (2);
	}
	if (argc == 6 && ft_atoi(argv[5]) == 0)
	{
		printf("Philosophers must eat at least one time\n");
		return (5);
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

void	init_nme(int argc, char **argv, t_options *opt)
{
	int i;

	i = -1;
	if (argc == 6)
	{
		opt->is_nme = 1;
		opt->nme = malloc(sizeof(int) * opt->philo_n);
		if (!opt->nme)
			return ;
		while (++i < opt->philo_n)
			opt->nme[i] = ft_atoi(argv[5]);
	}
	else
		opt->is_nme = 0;
}

int		main(int argc, char **argv)
{
	t_options	*opt;
	int			error_code;

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
	sem_unlink("semaphore");
	sem_unlink("sentence");
	opt->sem = sem_open("semaphore", O_CREAT, 0660, opt->philo_n);
	opt->sem_sent = sem_open("sentence", O_CREAT, 0660, 1);
	init_nme(argc, argv, opt);
	g_alive = 1;
	create_threads(opt);
	return (0);
}
