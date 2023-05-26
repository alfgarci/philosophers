/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <alfgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 19:15:59 by alfgarci          #+#    #+#             */
/*   Updated: 2023/05/26 13:05:01 by alfgarci         ###   ########.fr       */
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
	while (!get_death(ins))
	{
		if ((get_time_ms() - time_aux) >= ins->time_eat)
			break ;
		usleep(5);
	}
	add_num_eat(ins, philo);
	pthread_mutex_unlock(&(ins->forks[philo->right]));
	pthread_mutex_unlock(&(ins->forks[philo->left]));
}

static void	*rutine(void *void_philosopher)
{
	t_philo		*philo;
	t_instance	*ins;
	long int	time_aux;

	philo = (t_philo *)void_philosopher;
	ins = philo->copy_ins;
	while (!get_death(ins))
	{
		eat(philo, ins);
		if (get_all_eat(ins))
			break ;
		print_msg(get_act_time(ins), philo->id, SLEEP, ins);
		time_aux = get_time_ms();
		while (!get_death(ins))
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
		ins->arr_philo[i].last_meal = get_time_ms();
		pthread_create(&(ins->arr_philo[i].th), NULL,
			rutine, &(ins->arr_philo[i]));
		i += 2;
		usleep(200);
	}
	i = 1;
	while (i < ins->num_philos)
	{
		ins->arr_philo[i].last_meal = get_time_ms();
		pthread_create(&(ins->arr_philo[i].th), NULL,
			rutine, &(ins->arr_philo[i]));
		i += 2;
		usleep(200);
	}
}
