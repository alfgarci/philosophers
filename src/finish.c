/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <alfgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:42:09 by alfgarci          #+#    #+#             */
/*   Updated: 2023/05/21 17:59:26 by alfgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	finish_threads(t_instance *ins)
{
	int	i;

	i = -1;
	while (++i < ins->num_philos)
		pthread_join(ins->arr_philo[i].th, NULL);
}

static void	finish_mutex(t_instance *ins)
{
	int	i;

	i = -1;
	while (++i < ins->num_philos)
		pthread_mutex_destroy(&(ins->forks[i]));
	pthread_mutex_destroy(&(ins->writing_mutex));
	pthread_mutex_destroy(&(ins->eating_mutex));
}

void	finish_exe(t_instance *ins)
{
	finish_threads(ins);
	finish_mutex(ins);
	free_philo(ins);
}

void	free_philo(t_instance *ins)
{
	if (ins->forks)
		free(ins->forks);
	if (ins->arr_philo)
		free(ins->arr_philo);
	free(ins);
}