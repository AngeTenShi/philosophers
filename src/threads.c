/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 10:24:18 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/27 13:58:28 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	routine_eat(t_all *var, int *time_eat, int id)
{
	while (*time_eat < var->rules.time_to_eat)
	{
		if (var->philos[id].is_dead == 1)
			return (0);
		if (!eat(var, id, var->timer))
			return (0);
		(*time_eat)++;
	}
	return (1);
}

void	*routine(void *param)
{
	t_all			*var;
	int				id;
	int				time_eat;

	var = ((t_philo *)param)->all;
	id = ((t_philo *)param)->id;
	time_eat = var->rules.number_time_to_eat;
	while (1)
	{
		if (var->philos[id].is_dead == 1)
			return (NULL);
		if (time_eat != -1)
		{
			if (!routine_eat(var, &time_eat, id))
				return (NULL);
		}
		else
		{
			if (!eat(var, id, var->timer))
				return (NULL);
		}
	}
	return (NULL);
}

void	start_threads(t_all *var, int pair)
{
	int	i;

	i = pair;
	while (i < var->rules.number_of_philosophers)
	{
		pthread_create(&var->philos[i].thread, NULL, routine,
			(void *)&var->philos[i]);
		pthread_create(&var->philos[i].death_checker, NULL, check_death,
			(void *)&var->philos[i]);
		i += 2;
	}
}

void	wait_threads(t_all *var)
{
	int	i;

	i = 0;
	while (i < var->rules.number_of_philosophers)
	{
		pthread_join(var->philos[i].thread, NULL);
		i++;
	}
}

void	create_threads(t_all *var)
{
	int	size;

	size = var->rules.number_of_philosophers;
	gettimeofday(&var->timer, NULL);
	start_threads(var, 0);
	//my_sleep(100);
	start_threads(var, 1);
	wait_threads(var);
}
