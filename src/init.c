/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:08:22 by anggonza          #+#    #+#             */
/*   Updated: 2022/05/25 15:34:57 by anggonza         ###   ########.fr       */
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
}

void	*routine(void *test)
{
	printf("Its a thread \n");
	return (NULL);
}

void	init_philos(t_all *var)
{
	int	i;

	var->philos = malloc(sizeof(t_philo) * var->rules.number_of_philosophers);
	i = 0;
	while (i < var->rules.number_of_philosophers)
	{
		pthread_create(&var->philos[i].thread, NULL, &routine, NULL);
		var->philos[i].id = i + 1;
		var->philos[i].left_fork = i;
		var->philos[i].right_fork = (i + 1) % var->rules.number_of_philosophers;
		var->philos[i].is_eating = 0;
		i++;
	}
}
