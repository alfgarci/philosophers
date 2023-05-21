/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <alfgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:40:05 by alfgarci          #+#    #+#             */
/*   Updated: 2023/05/21 17:57:14 by alfgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_all_ate(t_instance *ins, t_philo *philos)
{
	int	i;

	i = 0;
	while (ins->num_eats != -1
		&& i < ins->num_philos && philos[i].eats >= (ins->num_eats - 1))
		i++;
	if (i == ins->num_philos)
		ins->all_ate = 1;
}

static void	check_death(t_instance *ins, t_philo *philo)
{
	if ((get_time_ms() - philo->last_meal) > ins->time_die)
	{
		print_msg(get_act_time(ins), philo->id, DIED, ins);
		ins->death = 1;
	}
}

void	checker(t_instance *ins)
{
	int		i;
	t_philo	*philos;

	philos = ins->arr_philo;
	while (!(ins->death) && !(ins->all_ate))
	{
		i = -1;
		while (++i < ins->num_philos && !(ins->death))
		{
			pthread_mutex_lock(&(ins->eating_mutex));
			check_death(ins, &philos[i]);
			pthread_mutex_unlock(&(ins->eating_mutex));
			usleep(50);
		}
		if (ins->death)
		{	
			pthread_mutex_unlock(&(ins->forks[philos->left]));
			pthread_mutex_unlock(&(ins->forks[philos->right]));
			break ;
		}
		check_all_ate(ins, philos);
	}
}
