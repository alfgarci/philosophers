/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <alfgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 19:01:01 by alfgarci          #+#    #+#             */
/*   Updated: 2023/05/26 11:18:54 by alfgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_instance	*ins;

	if (argc > 4 && argc < 7)
	{
		ins = init_data(argv);
		if (!ins)
		{
			printf("error: malloc problem\n");
			return (-1);
		}
		ins->init_time = get_time_ms();
		run_threads(ins);
		checker(ins);
		finish_exe(ins);
		return (0);
	}
	printf("error: Wrong number od parametres\n");
	return (-1);
}
