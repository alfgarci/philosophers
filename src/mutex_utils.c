/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <alfgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:26:01 by alfgarci          #+#    #+#             */
/*   Updated: 2023/05/26 13:04:58 by alfgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int get_death(t_instance *ins)
{
    int state;

	pthread_mutex_lock(&(ins->death_mutex));
    state = ins->death;
	pthread_mutex_unlock(&(ins->death_mutex));   
    return (state);
}

void    set_death(t_instance *ins, int state)
{
	pthread_mutex_lock(&(ins->death_mutex));
    ins->death = state;
	pthread_mutex_unlock(&(ins->death_mutex));   
}

int get_all_eat(t_instance *ins)
{
    int state;

	pthread_mutex_lock(&(ins->all_eat_mutex));
    state = ins->all_ate;
	pthread_mutex_unlock(&(ins->all_eat_mutex));   
    return (state);
}

void    set_all_eat(t_instance *ins, int state)
{
	pthread_mutex_lock(&(ins->all_eat_mutex));
    ins->all_ate = state;
	pthread_mutex_unlock(&(ins->all_eat_mutex));   
}

int get_num_eat(t_instance *ins, int i)
{
    int state;

	pthread_mutex_lock(&(ins->eating_mutex));
    state = ins->arr_philo[i].eats;
	pthread_mutex_unlock(&(ins->eating_mutex));   
    return (state);
}

void    add_num_eat(t_instance *ins, t_philo *philo)
{
	pthread_mutex_lock(&(ins->eating_mutex));
    philo->eats++;
	pthread_mutex_unlock(&(ins->eating_mutex));   
}
