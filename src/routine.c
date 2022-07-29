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

void	print_message(int type, t_all *var, int id, struct timeval timer)
{
	int	ms;

	pthread_mutex_lock(&var->print_mutex);
	ms = get_ms(timer);
	var->philos[id].last_meal_time = ms;
	if (type == FORK)
		printf("%d ms %d has taken a fork\n", ms, id);
	if (type == EAT)
		printf("%d ms %d is eating\n", ms, id);
	if (type == SLEEP)
		printf("%d ms %d is sleeping\n", ms, id);
	if (type == THINKING)
		printf("%d ms %d is thinking\n", ms, id);
	if (type == DIED)
		printf("%d ms %d died\n", ms, id);
	pthread_mutex_unlock(&var->print_mutex);
}

int	eat(t_all *var, int id, struct timeval timer)
{
	pthread_mutex_lock(&var->is_dead);
	if (var->one_is_dead == 1)
		return (0);
	pthread_mutex_unlock(&var->is_dead);
	pthread_mutex_lock(&var->mutex[var->philos[id].left_fork]);
	print_message(FORK, var, id, timer);
	pthread_mutex_lock(&var->mutex[var->philos[id].right_fork]);
	print_message(FORK, var, id, timer);
	print_message(EAT, var, id, timer);
	my_sleep(var->rules.time_to_eat);
	pthread_mutex_unlock(&var->mutex[var->philos[id].left_fork]);
	pthread_mutex_unlock(&var->mutex[var->philos[id].right_fork]);
	sleeping(var, id, timer);
	return (1);
}

void	sleeping(t_all *var, int id, struct timeval timer)
{
	pthread_mutex_lock(&var->is_dead);
	if (var->one_is_dead == 1)
		return ;
	pthread_mutex_unlock(&var->is_dead);
	print_message(SLEEP, var, id, timer);
	my_sleep(var->rules.time_to_sleep);
	print_message(THINKING, var, id, timer);
}
