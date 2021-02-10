/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 01:35:13 by pcariou           #+#    #+#             */
/*   Updated: 2021/02/10 23:29:18 by pcariou          ###   ########.fr       */
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

typedef struct		s_options
{
	int				philo_n;
	int				time_d;
	int				time_e;
	int				time_s;
	int				philo_id;
	int				is_nme;
	int				*nme;
	sem_t			*sem;
	sem_t			*sem_sent;
}					t_options;

int					g_alive;

int					ft_atoi(const char *str);
int					is_num(int argc, char **argv);
void				*philosopher(void *arg);
void				die_while_eating(struct timeval *tv,
					int id, t_options *opt);
void				die_in_action(struct timeval *tv, int id,
					t_options *opt, int time_a);
int					nme(t_options *opt, int id);
void				eating(struct timeval *tv, int id, t_options *opt);

#endif
