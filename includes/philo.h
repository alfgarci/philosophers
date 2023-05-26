/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <alfgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:29:26 by alfgarci          #+#    #+#             */
/*   Updated: 2023/05/26 11:35:35 by alfgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define ORANGE	"\x1B[38;2;255;128;0m"
# define RED	"\x1b[31m"
# define GREEN	"\x1b[32m"
# define YELLOW	"\x1b[33m"
# define BLUE	"\x1b[34m"

enum e_actions
{
	TAKE_FORK,
	EAT,
	SLEEP,
	THINK,
	DIED
};

typedef struct s_philo
{
	int					id;
	int					eats;
	int					left;
	int					right;
	long long			last_meal;
	struct s_instance	*copy_ins;
	pthread_t			th;
}						t_philo;

typedef struct s_instance
{
	int					num_philos;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					num_eats;
	int					death;
	int					all_ate;
	long long			init_time;
	pthread_mutex_t		eating_mutex;
	pthread_mutex_t		writing_mutex;
	pthread_mutex_t		all_eat_mutex;
	pthread_mutex_t		death_mutex;
	pthread_mutex_t		*forks;
	struct s_philo		*arr_philo;
}						t_instance;

/*init.c*/
t_instance	*init_data(char **argv);

/*philo.c*/
void		run_threads(t_instance *ins);

/*checker.c*/

void		checker(t_instance *ins);

/*finish.c*/
void		finish_exe(t_instance *ins);
void		free_philo(t_instance *ins);

/*mutex_utils.c*/
int			get_death(t_instance *ins);
void		set_death(t_instance *ins, int state);
int			get_all_eat(t_instance *ins);
void		set_all_eat(t_instance *ins, int state);

/*utils.c*/
int			ft_atoi(const char *str);
long int	get_act_time(t_instance *ins);
long int	get_time_ms(void);
void		print_msg(long int time, int id, int act, t_instance *ins);

#endif