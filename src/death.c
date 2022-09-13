/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 10:24:18 by anggonza          #+#    #+#             */
/*   Updated: 2022/08/08 12:53:21 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	everyone_dead(t_all *var)
{
	int	i;

	i = 0;
	var->one_is_dead = 1;
	while (i < var->rules.number_of_philosophers)
	{
		if (var->philos[i].is_dead != 1)
			var->philos[i].is_dead = 1;
		i++;
	}
}

int	calcul(t_all *var, int id)
{
	int	time_die;
	int	last_meal;

	time_die = var->rules.time_to_die;
	last_meal = var->philos[id].last_meal_time;
	if (get_ms(var->timer) >= time_die + last_meal && var->one_is_dead != 1
		&& var->philos[id].finish_eating == 0)
		return (1);
	else
		return (0);
}

void	*check_death(void *param)
{
	int		id;
	t_all	*var;

	var = ((t_philo *)param)->all;
	id = ((t_philo *)param)->id;
	while (1)
	{
		if (var->one_is_dead == 1 || var->philos[id].finish_eating == 1)
			break ;
		if (var->philos[id].is_eating == 0)
		{
			pthread_mutex_lock(&var->is_dead);
			if (calcul(var, id))
			{
				pthread_mutex_lock(&var->print_mutex);
				printf("%d %d died\n", get_ms(var->timer), id);
				pthread_mutex_unlock(&var->print_mutex);
				everyone_dead(var);
				pthread_mutex_unlock(&var->is_dead);
				break ;
			}
			pthread_mutex_unlock(&var->is_dead);
		}
	}
	return (NULL);
}
