/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:21:28 by anggonza          #+#    #+#             */
/*   Updated: 2022/08/08 11:48:52 by anggonza         ###   ########.fr       */
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

# define FORK 0
# define EAT 1
# define SLEEP 2
# define THINKING 3
# define DIED 4
# define OVERFLOW_MAX "2147483647"
# define OVERFLOW_MIN "-2147483648"

typedef struct s_all	t_all;

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
	int					id;
	int					left_fork;
	int					right_fork;
	int					last_meal_time;
	pthread_t			thread;
	pthread_t			death_checker;
	pthread_mutex_t		time_eat_mut;
	pthread_mutex_t		is_dead_mut;
	int					is_dead;
	int					time_eat;
	int					is_eating;
	int					finish_eating;
	t_all				*all;
}	t_philo;

typedef struct s_all
{
	pthread_mutex_t	*mutex;
	t_philo			*philos;
	t_rules			rules;
	pthread_t		death_check;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	is_dead;
	int				one_is_dead;
	struct timeval	timer;
}	t_all;

void	init_rules(t_all *var, char **av, int optionnel);
void	init_philos(t_all *var);
void	init_mutex(t_all *var);
void	create_threads(t_all *var);
int		print_message(int type, t_all *var, int id, struct timeval timer);
int		sleeping(t_all *var, int id, struct timeval timer);
int		eat(t_all *var, int id, struct timeval timer);
void	my_sleep(int time_to_sleep);
int		get_ms(struct timeval begin);
int		parse_args(int ac, char **av, t_all *var);
void	*check_death(void *param);
int		check_eat_time(t_all *var, int id);
int		check_fork(t_all *var, int id, struct timeval timer);

#endif
