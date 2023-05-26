/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <alfgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 19:15:01 by alfgarci          #+#    #+#             */
/*   Updated: 2023/05/26 11:36:04 by alfgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	check_valid_param(t_instance *ins)
{
	if (ins->num_philos < 1 || ins->num_philos > 200 || ins->time_die < 60
		|| ins->time_eat < 60 || ins->time_sleep < 60)
		return (1);
	else
		return (0);
}

static void	init_mutex(t_instance *ins)
{
	int	i;

	i = -1;
	while (++i < ins->num_philos)
		pthread_mutex_init(&(ins->forks[i]), NULL);
	pthread_mutex_init(&(ins->writing_mutex), NULL);
	pthread_mutex_init(&(ins->eating_mutex), NULL);
	pthread_mutex_init(&(ins->all_eat_mutex), NULL);
	pthread_mutex_init(&(ins->death_mutex), NULL);
}

static void	init_philo(t_instance *ins)
{
	int	i;

	i = -1;
	while (++i < ins->num_philos)
	{
		ins->arr_philo[i].id = i + 1;
		ins->arr_philo[i].left = i;
		ins->arr_philo[i].right = (i + 1) % ins->num_philos;
		ins->arr_philo[i].eats = 0;
		ins->arr_philo[i].last_meal = 0;
		ins->arr_philo[i].copy_ins = ins;
	}
}

void	set_param(t_instance *ins, char **argv)
{
	ins->num_philos = ft_atoi(argv[1]);
	ins->time_die = ft_atoi(argv[2]);
	ins->time_eat = ft_atoi(argv[3]);
	ins->time_sleep = ft_atoi(argv[4]);
	ins->all_ate = 0;
	ins->death = 0;
	if (argv[5])
		ins->num_eats = ft_atoi(argv[5]);
	else
		ins->num_eats = -1;
}

t_instance	*init_data(char **argv)
{
	t_instance	*ins;

	ins = (t_instance *)malloc(sizeof(t_instance));
	if (!ins)
		return (NULL);
	set_param(ins, argv);
	if (check_valid_param(ins) == 1)
	{
		free_philo(ins);
		return (NULL);
	}
	ins->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* ins->num_philos);
	ins->arr_philo = (t_philo *)malloc(sizeof(t_philo) * ins->num_philos);
	if (!ins->forks || !ins->arr_philo)
	{
		free_philo(ins);
		return (NULL);
	}
	init_philo(ins);
	init_mutex(ins);
	return (ins);
}
