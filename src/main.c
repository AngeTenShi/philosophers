/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 11:54:34 by anggonza          #+#    #+#             */
/*   Updated: 2022/08/08 11:22:37 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	free_everything(t_all *var)
{
	int	i;

	i = 0;
	while (i < var->rules.number_of_philosophers)
	{
		pthread_mutex_destroy(&var->mutex[i]);
		pthread_mutex_destroy(&var->philos[i].time_eat_mut);
		i++;
	}
	free(var->philos);
	free(var->mutex);
	pthread_mutex_destroy(&var->is_dead);
	pthread_mutex_destroy(&var->print_mutex);
	free(var);
	return (1);
}

int	main(int ac, char **av)
{
	t_all	*var;

	var = malloc(sizeof(t_all));
	if (!parse_args(ac, av, var))
	{
		free(var);
		return (-1);
	}
	init_mutex(var);
	init_philos(var);
	create_threads(var);
	return (free_everything(var));
}
