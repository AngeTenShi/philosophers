/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:08:22 by anggonza          #+#    #+#             */
/*   Updated: 2022/08/08 12:22:05 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_mutex(t_all *var)
{
	int	i;

	i = 0;
	var->mutex = malloc(sizeof(pthread_mutex_t)
			* var->rules.number_of_philosophers);
	while (i < var->rules.number_of_philosophers)
	{
		pthread_mutex_init(&var->mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&var->print_mutex, NULL);
	pthread_mutex_init(&var->is_dead, NULL);
}

void	init_rules(t_all *var, char **av, int optionnel)
{
	var->rules.number_of_philosophers = ft_atoi(av[1]);
	var->rules.time_to_die = ft_atoi(av[2]);
	var->rules.time_to_eat = ft_atoi(av[3]);
	var->rules.time_to_sleep = ft_atoi(av[4]);
	if (!optionnel)
		var->rules.number_time_to_eat = -1;
	else
		var->rules.number_time_to_eat = ft_atoi(av[5]);
	var->one_is_dead = 0;
}

void	init_philos(t_all *var)
{
	int	i;

	var->philos = malloc(sizeof(t_philo) * var->rules.number_of_philosophers);
	i = 0;
	while (i < var->rules.number_of_philosophers)
	{
		var->philos[i].id = i;
		var->philos[i].left_fork = i;
		var->philos[i].right_fork = (i + 1) % var->rules.number_of_philosophers;
		var->philos[i].all = var;
		var->philos[i].last_meal_time = 0;
		var->philos[i].time_eat = 0;
		var->philos[i].is_dead = 0;
		var->philos[i].is_eating = 0;
		var->philos[i].finish_eating = 0;
		pthread_mutex_init(&var->philos[i].time_eat_mut, NULL);
		pthread_mutex_init(&var->philos[i].is_dead_mut, NULL);
		i++;
	}
}
