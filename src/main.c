/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 11:54:34 by anggonza          #+#    #+#             */
/*   Updated: 2022/05/25 15:16:55 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_all	var;

	if (ac < 5 || ac > 6)
	{
		ft_putstr_fd("Error not enougth arguments\n", 2);
		return (0);
	}
	if (ac == 5)
		init_rules(&var, av, 0);
	else
		init_rules(&var, av, 1);
	init_mutex(&var);
	init_philos(&var);
	//start_threads();
	//return (free_everything(&var));
	return (0);
}
