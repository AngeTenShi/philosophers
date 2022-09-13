/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 10:24:18 by anggonza          #+#    #+#             */
/*   Updated: 2022/08/08 12:34:25 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_eat_time(t_all *var, int id)
{
	if (var->philos[id].time_eat == -1)
		return (1);
	if (var->philos[id].time_eat == var->rules.number_time_to_eat)
	{
		var->philos[id].finish_eating = 1;
		return (0);
	}
	else
		return (1);
}

int	routine_eat(t_all *var, int id)
{
	while (1)
	{
		if (var->philos[id].is_dead == 1)
			return (0);
		if (!eat(var, id, var->timer))
			return (0);
	}
}

void	*routine(void *param)
{
	t_all			*var;
	int				id;
	int				time_eat;

	var = ((t_philo *)param)->all;
	id = ((t_philo *)param)->id;
	time_eat = var->rules.number_time_to_eat;
	if (id % 2 == 1)
		my_sleep(var->rules.time_to_eat);
	while (1)
	{
		if (time_eat != -1)
		{
			if (!routine_eat(var, id))
				return (NULL);
		}
		else if (!eat(var, id, var->timer) || var->one_is_dead == 1)
			return (NULL);
	}
}

void	start_threads(t_all *var)
{
	int	i;

	i = 0;
	while (i < var->rules.number_of_philosophers)
	{
		pthread_create(&var->philos[i].thread, NULL, routine,
			(void *)&var->philos[i]);
		pthread_create(&var->philos[i].death_checker, NULL, check_death,
			(void *)&var->philos[i]);
		i++;
	}
	i = 0;
	while (i < var->rules.number_of_philosophers)
	{
		pthread_join(var->philos[i].thread, NULL);
		pthread_join(var->philos[i].death_checker, NULL);
		i++;
	}
}

void	create_threads(t_all *var)
{
	gettimeofday(&var->timer, NULL);
	start_threads(var);
}
