/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:20:13 by pcariou           #+#    #+#             */
/*   Updated: 2021/02/04 15:02:12 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_one.h"

int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int		is_num(int argc, char **argv)
{
	int i;
	int k;

	i = 0;
	k = -1;
	while (++i < argc)
	{
		while (argv[i][++k])
		{
			if (!ft_isdigit(argv[i][k]))
				return (0);
		}
		k = -1;
	}
	return (1);
}

int		ft_atoi(const char *str)
{
	int i;
	int minus;
	int num;

	i = 0;
	minus = 0;
	num = 0;
	while (str[i] == '\t' || str[i] == '\n' ||
			str[i] == '\r' || str[i] == '\v' ||
			str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus++;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num *= 10;
		num += (str[i] - '0');
		i++;
	}
	(minus == 1) ? num *= -1 : num;
	return (num);
}
