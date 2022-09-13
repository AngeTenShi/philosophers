/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 10:24:32 by anggonza          #+#    #+#             */
/*   Updated: 2022/08/08 12:42:42 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	my_sleep(int time_to_sleep)
{
	struct timeval	start;
	struct timeval	end;
	int				time;

	gettimeofday(&start, NULL);
	gettimeofday(&end, NULL);
	time = 0;
	while (time < time_to_sleep)
	{
		time = ((end.tv_sec - start.tv_sec) * 1000)
				 + ((end.tv_usec - start.tv_usec) / 1000);
		gettimeofday(&end, NULL);
		usleep(100);
	}
}

int	get_ms(struct timeval begin)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
	return ((end.tv_sec - begin.tv_sec) * 1000
		+ (end.tv_usec - begin.tv_usec) / 1000);
}