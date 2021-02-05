#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct	s_options
{
	int	philo_n;
	int	time_d;
	int time_e;
	int	time_s;
}				t_options;


pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;
int*	g_forks;
int		g_id;
int		g_alive;

int		ft_atoi(const char *str);
int		is_num(int argc, char **argv);

#endif
