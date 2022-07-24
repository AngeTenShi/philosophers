#include "philosophers.h"

void	print_message(int type, t_all *var, int id)
{
	pthread_mutex_lock(&var->print_mutex);
	if (type == FORK)
		printf("%d has taken a fork\n", id);
	if (type == EAT)
		printf("%d is eating\n", id);
	if (type == SLEEP)
		printf("%d is sleeping\n", id);
	if (type == THINKING)
		printf("%d is thinking\n", id);
	pthread_mutex_unlock(&var->print_mutex);
}

void	eat(t_all *var, int id)
{
	print_message(EAT, var, id);
	my_sleep(var->rules.time_to_eat);
	pthread_mutex_unlock(&var->mutex[var->philos[id].left_fork]);
	pthread_mutex_unlock(&var->mutex[var->philos[id].right_fork]);
	sleeping(var, id);
}

void	sleeping(t_all *var, int id)
{
	print_message(SLEEP, var, id);
	my_sleep(var->rules.time_to_sleep);
	print_message(THINKING, var, id);
}

void take_forks(t_all *var, int id)
{
	pthread_mutex_lock(&var->mutex[var->philos[id].left_fork]);
	print_message(FORK, var, id);
	pthread_mutex_lock(&var->mutex[var->philos[id].right_fork]);
	print_message(FORK, var, id);
}
