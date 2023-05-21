/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 19:15:59 by alfgarci          #+#    #+#             */
/*   Updated: 2023/05/13 19:16:01 by alfgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *philo, t_instance *ins)
{
	long int	time_aux;

	pthread_mutex_lock(&(ins->forks[philo->left]));
	print_msg(get_act_time(ins), philo->id, TAKE_FORK, ins);
	pthread_mutex_lock(&(ins->forks[philo->right]));
	print_msg(get_act_time(ins), philo->id, TAKE_FORK, ins);
	pthread_mutex_lock(&(ins->eating_mutex));
	print_msg(get_act_time(ins), philo->id, EAT, ins);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&(ins->eating_mutex));
	time_aux = get_time_ms();
	while (!(ins->death))
	{
		if ((get_time_ms() - time_aux) >= ins->time_eat)
			break ;
		usleep(5);
	}
	(philo->eats)++;
	pthread_mutex_unlock(&(ins->forks[philo->left]));
	pthread_mutex_unlock(&(ins->forks[philo->right]));
}

static void	*rutine(void *void_philosopher)
{
	t_philo		*philo;
	t_instance	*ins;
	long int	time_aux;

	philo = (t_philo *)void_philosopher;
	ins = philo->copy_ins;
	while (!(ins->death))
	{
		eat(philo, ins);
		if (ins->all_ate)
			break ;
		print_msg(get_act_time(ins), philo->id, SLEEP, ins);
		time_aux = get_time_ms();
		while (!(ins->death))
		{
			if ((get_time_ms() - time_aux) >= ins->time_eat)
				break ;
			usleep(5);
		}
		print_msg(get_act_time(ins), philo->id, THINK, ins);
	}
	return (NULL);
}

void	run_threads(t_instance *ins)
{
	int	i;

	i = 0;
	while (i < ins->num_philos)
	{
		pthread_create(&(ins->arr_philo[i].th), NULL,
			rutine, &(ins->arr_philo[i]));
		ins->arr_philo[i].last_meal = get_time_ms();
		i += 2;
	}
	i = 1;
	while (i < ins->num_philos)
	{
		pthread_create(&(ins->arr_philo[i].th), NULL,
			rutine, &(ins->arr_philo[i]));
		ins->arr_philo[i].last_meal = get_time_ms();
		i += 2;
	}
}
