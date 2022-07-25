/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 10:24:18 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/25 14:39:37 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *param)
{
	t_all			*var;
	int				id;
	int				time_eat;
	struct timeval	timer;

	gettimeofday(&timer, NULL);
	var = ((t_philo *)param)->all;
	id = ((t_philo *)param)->id;
	time_eat = var->rules.number_time_to_eat;
	if (time_eat != -1)
	{
		while (time_eat < var->rules.time_to_eat)
		{
			take_forks(var, id, timer);
			eat(var, id, timer);
			time_eat++;
		}
	}
	else
	{
		take_forks(var, id, timer);
		eat(var, id, timer);
	}
	return (NULL);
}

void	start_threads(t_all *var)
{
	int	i;

	i = 0;
	while (i < var->rules.number_of_philosophers)
	{
		pthread_create(&var->philos[i].thread, NULL, routine,
			(void *)&var->philos[i]);
		i += 2;
	}
	i = 1;
	while (i < var->rules.number_of_philosophers)
	{
		pthread_create(&var->philos[i].thread, NULL, routine,
			(void *)&var->philos[i]);
		i += 2;
	}
}

void	create_threads(t_all *var)
{
	int	i;

	start_threads(var);
	i = 0;
	while (i < var->rules.number_of_philosophers)
	{
		pthread_join(var->philos[i].thread, NULL);
		i++;
	}
}
