/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:39:38 by anggonza          #+#    #+#             */
/*   Updated: 2022/06/07 15:26:13 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_state(t_all *var, char state)
{
	pthread_mutex_lock(&var->rules.print);
	if (state == 'e')
		printf("%d is eating\n", var->philos[var->id_actual].id);
	if (state == 's')
		printf("%d is sleeping\n", var->philos[var->id_actual].id);
	if (state == 'f')
		printf("%d has taken a fork\n", var->philos[var->id_actual].id);
	pthread_mutex_unlock(&var->rules.print);
}

void	eat(t_all *var)
{
	struct timeval	begin_eat;

	pthread_mutex_lock(&var->philos[var->id_actual].left_fork);
	print_state(var, 'f');
	pthread_mutex_lock(var->philos[var->id_actual].right_fork);
	print_state(var, 'f');
	print_state(var, 'e');
	usleep(500);
	pthread_mutex_unlock(&var->philos[var->id_actual].left_fork);
	pthread_mutex_unlock(var->philos[var->id_actual].right_fork);
	print_state(var, 's');
}

void	take_fork(t_all *var)
{
	return ;
}

void	time_to_sleep(t_all *var)
{
	usleep(var->rules.time_to_sleep);
}
