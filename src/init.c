/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:08:22 by anggonza          #+#    #+#             */
/*   Updated: 2022/06/03 15:26:07 by anggonza         ###   ########.fr       */
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

void	*routine(void *param)
{
	t_all	*var;
	int	id;
	int	time_eat;

	var = (t_all *)param;
	id = var->i;
	time_eat = var->rules.number_time_to_eat;
	if (time_eat != -1)
	{
		while (time_eat < var->rules.time_to_eat)
		{
			take_forks(var, id);
			eat(var, id);
			time_eat++;
		}
	}
	else
	{
		take_forks(var, id);
		eat(var, id);
	}
	return (NULL);
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
		var->philos[i].is_eating = 0;
		i++;
	}
}

void	create_threads(t_all *var)
{
	int	i;

	i = 0;
	while (i < var->rules.number_of_philosophers)
	{
		var->i = i;
		pthread_create(&var->philos[i].thread, NULL, routine, (void *)var);
		//	pthread_join(var->philos[i].thread, NULL);
		i += 2;
	}
	i = 1;
	while (i < var->rules.number_of_philosophers)
	{
		var->i = i;
		pthread_create(&var->philos[i].thread, NULL, routine, (void *)var);
	//	pthread_join(var->philos[i].thread, NULL);
		i += 2;
	}
	i = 0;
	while (i < var->rules.number_of_philosophers)
	{
		pthread_join(var->philos[i].thread, NULL);
		i++;
	}
}
