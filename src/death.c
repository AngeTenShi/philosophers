/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 10:24:18 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/25 16:06:41 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int check_death(t_all *var, int id)
{
	int	time;
	int	tmp;

	if (var->philos[id].last_meal_time == -1)
	{
		tmp = var->philos[id].last_meal_time + 1;
		time = get_ms(var->timer) - var->philos[id].last_meal_time;
		if (time >= var->rules.time_to_die)
			return (1);
	}
	else
	{
		time = get_ms(var->timer) - var->philos[id].last_meal_time;
		if (time >= var->rules.time_to_die)
			return (1);
	}
	return (0);
}