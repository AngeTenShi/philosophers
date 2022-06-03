/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:21:28 by anggonza          #+#    #+#             */
/*   Updated: 2022/06/03 14:36:54 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include "../libft/libft.h"
# include <stdio.h>

typedef struct s_rules
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_time_to_eat;
}	t_rules;

typedef struct s_philo
{
	int			id;
	int			left_fork;
	int			right_fork;
	int			is_eating;
	pthread_t	thread;
}	t_philo;

typedef struct s_all
{
	pthread_mutex_t	*mutex;
	t_philo			*philos;
	t_rules			rules;
}	t_all;

void	init_rules(t_all *var, char **av, int optionnel);
void	init_philos(t_all *var);
void	init_mutex(t_all *var);

#endif
