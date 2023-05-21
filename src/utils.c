/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 19:16:24 by alfgarci          #+#    #+#             */
/*   Updated: 2023/05/13 19:16:25 by alfgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int				i;
	int				sing;
	unsigned int	n;

	i = 0;
	n = 0;
	sing = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sing = -1;
	while (str[i] >= '0' && str[i] <= '9')
		n = n * 10 + (str[i++] - 48);
	if (n > 2147483647 && sing == 1)
		return (-1);
	else if (n > 2147483648 && sing == -1)
		return (0);
	return (n * sing);
}

long int	get_time_ms(void)
{
	struct timeval	moment;
	long int		sec;
	long int		m_sec;

	gettimeofday(&moment, NULL);
	sec = moment.tv_sec * 1000;
	m_sec = moment.tv_usec / 1000;
	return (sec + m_sec);
}

long int	get_act_time(t_instance *ins)
{
	return (get_time_ms() - ins->init_time);
}

void	print_msg(long int time, int id, int act, t_instance *ins)
{
	pthread_mutex_lock(&(ins->writing_mutex));
	if (!(ins->death))
	{
		if (act == TAKE_FORK)
			printf(BLUE "%li %i is has taken a fork\n", time, id);
		else if (act == EAT)
			printf(GREEN "%li %i is eating\n", time, id);
		else if (act == SLEEP)
			printf(ORANGE "%li %i is sleeping\n", time, id);
		else if (act == THINK)
			printf(YELLOW "%li %i is thinking\n", time, id);
		else if (act == DIED)
			printf(RED "%li %i died\n", time, id);
	}
	pthread_mutex_unlock(&(ins->writing_mutex));
}
