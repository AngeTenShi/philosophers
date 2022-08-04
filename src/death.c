/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 10:24:18 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/27 12:32:27 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	everyone_dead(t_all *var)
{
	int i;

	i = 0;
	while (i < var->rules.number_of_philosophers)
	{
		if (var->philos[i].is_dead != 1)
			var->philos[i].is_dead = 1;
		i++;
	}
}


void	*check_death(void *param)
{
	int		time;
	int		tmp;
	int		id;
	t_all	*var;

	var = ((t_philo *)param)->all;
	id = ((t_philo *)param)->id;
	while (1)
	{
		if (var->one_is_dead == 1)
			break ;
		if (var->philos[id].last_meal_time == -1)
			continue ;
		if (var->philos[id].is_eating == 0 && var->philos[id].first_meal == 0)
		{
			time = get_ms(var->timer) - var->philos[id].last_meal_time;
			if (time >= var->rules.time_to_die && var->one_is_dead != 1 && var->philos[id].finish_eating == 0)
			{
				if (pthread_mutex_lock(&var->is_dead))
					return (NULL);
				var->one_is_dead = 1;
				printf("%d ms %d died\n", get_ms(var->timer), id);
				everyone_dead(var);
				if (pthread_mutex_unlock(&var->is_dead))
					return (NULL);
				break ;
			}

		}
	}
	return (NULL);
}
