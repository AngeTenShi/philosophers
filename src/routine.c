/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 10:24:23 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/27 13:59:33 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_message(int type, t_all *var, int id, struct timeval timer)
{
	int	ms;

	pthread_mutex_lock(&var->philos[id].is_dead_mut);
	ms = get_ms(timer);
	if (var->one_is_dead == 1)
	{
		pthread_mutex_unlock(&var->philos[id].is_dead_mut);
		return (0);
	}
	pthread_mutex_unlock(&var->philos[id].is_dead_mut);
	if (pthread_mutex_lock(&var->print_mutex))
		return (0);
	var->philos[id].last_meal_time = get_ms(var->timer);
	if (type == FORK)
		printf("%d ms %d has taken a fork\n", ms, id);
	if (type == EAT)
		printf("%d ms %d is eating\n", ms, id);
	if (type == SLEEP)
		printf("%d ms %d is sleeping\n", ms, id);
	if (type == THINKING)
		printf("%d ms %d is thinking\n", ms, id);
	if (pthread_mutex_unlock(&var->print_mutex))
		return (0);
	return (1);
}

int	eat(t_all *var, int id, struct timeval timer)
{
	pthread_mutex_lock(&var->philos[id].time_eat_mut);
	if (!check_eat_time(var, id))
		return (0);
	pthread_mutex_unlock(&var->philos[id].time_eat_mut);
	pthread_mutex_lock(&var->mutex[var->philos[id].left_fork]);
	if (!print_message(FORK, var, id, timer))
		return (0);
	pthread_mutex_lock(&var->mutex[var->philos[id].right_fork]);
	if (!print_message(FORK, var, id, timer))
		return (0);
	if (!print_message(EAT, var, id, timer))
		return (0);
	var->philos[id].time_eat++;
	var->philos[id].is_eating = 1;
	my_sleep(var->rules.time_to_eat);
	var->philos[id].is_eating = 0;
	pthread_mutex_unlock(&var->mutex[var->philos[id].left_fork]);
	pthread_mutex_unlock(&var->mutex[var->philos[id].right_fork]);
	var->philos[id].first_meal = 0;
	if (var->philos[id].time_eat == var->rules.time_to_eat)
		return (0);
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
