/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 01:35:13 by pcariou           #+#    #+#             */
/*   Updated: 2021/02/07 01:37:14 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct		s_options
{
	int				philo_n;
	int				time_d;
	int				time_e;
	int				time_s;
	int				philo_id;
	pthread_mutex_t	*locks;
}					t_options;

int					g_alive;

int					ft_atoi(const char *str);
int					is_num(int argc, char **argv);
void				*philosopher(void *arg);

#endif
