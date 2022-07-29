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

void	routine_eat(t_all *var, int *time_eat, int id)
{
	while (*time_eat < var->rules.time_to_eat)
	{
		eat(var, id, var->timer);
		(*time_eat)++;
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
	while (1)
	{
		if (time_eat != -1)
		{
			routine_eat(var, &time_eat, id);
			break ;
		}
		else
		{
			eat(var, id, var->timer);
			break ;
		}
	}
	return (NULL);
}

void	start_threads(t_all *var, int pair)
{
	int	i;

	i = pair;
	while (i < var->rules.number_of_philosophers - 1)
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
		pthread_join(var->philos[i].death_checker, NULL);
		i++;
	}
}

void	create_threads(t_all *var)
{
	int	size;

	size = var->rules.number_of_philosophers;
	gettimeofday(&var->timer, NULL);
	if ((size - 1) % 2 == 0)
	{
		start_threads(var, 0);
		pthread_create(&var->philos[size - 1].thread, NULL, routine,
			(void *)&var->philos[size - 1]);
		pthread_create(&var->philos[size - 1].death_checker, NULL, routine,
			(void *)&var->philos[size - 1]);
		my_sleep(100);
		start_threads(var, 1);
	}
	else
	{
		start_threads(var, 0);
		my_sleep(100);
		start_threads(var, 1);
		wait_threads(var);
	}
}
