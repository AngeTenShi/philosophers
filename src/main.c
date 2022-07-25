/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 11:54:34 by anggonza          #+#    #+#             */
/*   Updated: 2022/06/03 15:07:17 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_all	*var;

	var = malloc(sizeof(t_all));
	if (!parse_args(ac, av, var))
		return (-1);
	init_mutex(var);
	init_philos(var);
	create_threads(var);
	free(var);
	return (0);
}
//return (free_everything(&var));
