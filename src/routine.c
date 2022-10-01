/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 10:24:23 by anggonza          #+#    #+#             */
/*   Updated: 2022/10/01 11:55:32 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_message(int type, t_all *var, int id, struct timeval timer)
{
	int	ms;

	pthread_mutex_lock(&var->is_dead_mut);
	ms = get_ms(timer);
	if (type == EAT)
		var->philos[id].last_meal_time = ms;
	if (var->one_is_dead == 1)
	{
		pthread_mutex_unlock(&var->is_dead_mut);
		return (0);
	}
	pthread_mutex_unlock(&var->is_dead_mut);
	if (pthread_mutex_lock(&var->print_mutex))
		return (0);
	if (type == FORK)
		printf("%d %d has taken a fork\n", ms, id);
	if (type == EAT)
		printf("%d %d is eating\n", ms, id);
	if (type == SLEEP)
		printf("%d %d is sleeping\n", ms, id);
	if (type == THINKING)
		printf("%d %d is thinking\n", ms, id);
	if (pthread_mutex_unlock(&var->print_mutex))
		return (0);
	return (1);
}

int	check_fork(t_all *var, int id, struct timeval timer)
{
	if (var->philos[id].left_fork == var->philos[id].right_fork)
	{
		pthread_mutex_lock(&var->mutex[var->philos[id].left_fork]);
		print_message(FORK, var, id, timer);
		my_sleep(var->rules.time_to_die);
		pthread_mutex_unlock(&var->mutex[var->philos[id].left_fork]);
	}
	else
	{
		pthread_mutex_lock(&var->philos[id].time_eat_mut);
		if (!check_eat_time(var, id))
		{
			pthread_mutex_unlock(&var->philos[id].time_eat_mut);
			return (0);
		}
		var->philos[id].time_eat++;
		pthread_mutex_unlock(&var->philos[id].time_eat_mut);
		pthread_mutex_lock(&var->mutex[var->philos[id].left_fork]);
		if (!print_message(FORK, var, id, timer))
			return (0);
		pthread_mutex_lock(&var->mutex[var->philos[id].right_fork]);
		if (!print_message(FORK, var, id, timer))
			return (0);
	}
	return (1);
}

int	eat(t_all *var, int id, struct timeval timer)
{
	var->philos[id].is_eating = 0;
	if (!check_fork(var, id, var->timer))
		return (0);
	if (!print_message(EAT, var, id, timer))
		return (0);
	var->philos[id].is_eating = 1;
	my_sleep(var->rules.time_to_eat);
	var->philos[id].is_eating = 0;
	pthread_mutex_unlock(&var->mutex[var->philos[id].left_fork]);
	pthread_mutex_unlock(&var->mutex[var->philos[id].right_fork]);
	if (!sleeping(var, id, timer))
		return (0);
	return (1);
}

int	sleeping(t_all *var, int id, struct timeval timer)
{
	if (!print_message(SLEEP, var, id, timer))
		return (0);
	my_sleep(var->rules.time_to_sleep);
	if (!print_message(THINKING, var, id, timer))
		return (0);
	return (1);
}
