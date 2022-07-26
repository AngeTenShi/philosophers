/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 10:24:18 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/26 12:10:28 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*check_death(void *param)
{
	int		time;
	int		tmp;
	int		id;
	t_all	*var;

	var = ((t_philo *)param)->all;
	id = ((t_philo *)param)->id;
	while (var->one_is_dead == 0)
	{
		if (var->one_is_dead == 1)
		{
			var->philos[id].is_dead = 1;
			sleep(1000);
		}
		if (var->philos[id].last_meal_time == -1)
		{
			tmp = var->philos[id].last_meal_time + 1;
			time = get_ms(var->timer) - var->philos[id].last_meal_time;
			if (time >= var->rules.time_to_die)
				var->one_is_dead = 1;
		}
		else
		{
			time = get_ms(var->timer) - var->philos[id].last_meal_time;
			if (time >= var->rules.time_to_die)
				var->one_is_dead = 1;
		}

	}
	return (NULL);
}
