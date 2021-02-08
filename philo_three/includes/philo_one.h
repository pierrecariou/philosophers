/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 01:35:13 by pcariou           #+#    #+#             */
/*   Updated: 2021/02/08 01:26:59 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <signal.h>

typedef struct		s_options
{
	int				philo_n;
	int				time_d;
	int				time_e;
	int				time_s;
	int				philo_id;
	sem_t			*sem;
	sem_t			*sem_sent;
	sem_t			*sem_died;
	int				*pid;
}					t_options;

int					ft_atoi(const char *str);
int					is_num(int argc, char **argv);
void				*philosopher(void *arg);

#endif
