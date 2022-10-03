/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 10:24:18 by anggonza          #+#    #+#             */
/*   Updated: 2022/10/03 11:03:19 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

int	everyone_finish_eat(t_all *var)
{
	int	i;
	int	count;

	count = 1;
	i = 0;
	while (i < var->rules.number_of_philosophers)
	{
		if (var->philos[i].finish_eating == 1)
			count++;
		i++;
	}
	if (count == var->rules.number_of_philosophers)
		return (1);
	return (0);
}

int	to_be_continued(t_all *var, int id)
{
	if (everyone_finish_eat(var) && var->rules.number_of_philosophers != 1)
		return (0);
	if (var->philos[id].is_eating == 0)
	{
		pthread_mutex_lock(&var->is_dead);
		if (calcul(var, id))
		{
			pthread_mutex_lock(&var->print_mutex);
			printf("%d %d died\n", get_ms(var->timer), id);
			pthread_mutex_unlock(&var->print_mutex);
			var->one_is_dead = 1;
			pthread_mutex_unlock(&var->is_dead);
			return (0);
		}
		pthread_mutex_unlock(&var->is_dead);
	}
	return (1);
}

void	*check_death(void *param)
{
	t_all	*var;
	int		id;

	id = 0;
	var = (t_all *)param;
	while (1)
	{
		while (id < var->rules.number_of_philosophers)
		{
			if (var->one_is_dead == 1)
				break ;
			if (var->philos[id].finish_eating == 1)
			{
				id++;
				continue ;
			}
			if (!to_be_continued(var, id))
				return (NULL);
			id++;
		}
		id = 0;
	}
	return (NULL);
}
