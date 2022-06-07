/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:21:28 by anggonza          #+#    #+#             */
/*   Updated: 2022/06/07 15:02:05 by anggonza         ###   ########.fr       */
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
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_time_to_eat;
	pthread_mutex_t	print;
}	t_rules;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	eat_die;
	struct timeval	end_time;
}	t_philo;

typedef struct s_all
{
	t_philo			*philos;
	t_rules			rules;
	int				id_actual;
	struct timeval	begin_time;
}	t_all;

void	init_rules(t_all *var, char **av, int optionnel);
void	init_philos(t_all *var);
void	init_mutex(t_all *var);
void	eat(t_all *var);
void	time_to_sleep(t_all *var);
void	take_fork(t_all *var);

#endif
