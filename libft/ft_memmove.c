/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 18:29:58 by anggonza          #+#    #+#             */
/*   Updated: 2021/11/02 16:26:04 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = -1;
	if (src == dst)
		return (dst);
	else if (src < dst)
	{
		i = n;
		while (i-- > 0)
			*((unsigned char *)(dst + i)) = *((unsigned char *)(src + i));
	}
	else
	{
		while (++i < n)
			*((unsigned char *)(dst + i)) = *((unsigned char *)(src + i));
	}
	return (dst);
}
