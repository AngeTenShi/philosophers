/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:08:22 by anggonza          #+#    #+#             */
/*   Updated: 2022/06/07 15:20:51 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_mutex(t_all *var)
{
	int	i;

	i = 0;
	while (i < var->rules.number_of_philosophers)
	{
		pthread_mutex_init(&var->philos[i].left_fork, NULL);
		i++;
	}
	pthread_mutex_init(&var->rules.print, NULL);
}

void	init_rules(t_all *var, char **av, int optionnel)
{
	var->rules.number_of_philosophers = ft_atoi(av[1]);
	var->rules.time_to_die = ft_atoi(av[2]);
	var->rules.time_to_eat = ft_atoi(av[3]);
	var->rules.time_to_sleep = ft_atoi(av[4]);
	if (!optionnel)
	{
		var->rules.number_time_to_eat = -1;
	}
	else
	{
		var->rules.number_time_to_eat = ft_atoi(av[5]);
	}
	var->philos = malloc(sizeof(t_philo) * var->rules.number_of_philosophers);
}

void	*routine(void *param)
{
	t_all	*var;

	var = (t_all *)param;
	if (var->id_actual % 2 == 0)
		usleep(10);
	//take_fork(var);
	eat(var);
	time_to_sleep(var);
	return (NULL);
}

void	init_philos(t_all *var)
{
	int	i;

	if (var->rules.number_of_philosophers == 1)
		return ;
	i = 0;
	gettimeofday(&var->begin_time, NULL);
	while (i < var->rules.number_of_philosophers)
	{
		var->philos[i].id = i + 1;
		var->philos[i].right_fork = &var->philos[(i + 1) % var->rules.number_of_philosophers].left_fork;
		var->id_actual = i;
		pthread_create(&var->philos[i].thread, NULL, &routine, var);
		usleep(100);
		pthread_detach(var->philos[i].thread);
		usleep(100);
		i++;
	}
}
