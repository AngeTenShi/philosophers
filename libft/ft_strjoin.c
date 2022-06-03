/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:25:55 by anggonza          #+#    #+#             */
/*   Updated: 2021/11/02 16:29:06 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	size;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	str = malloc(size + 1);
	if (!str)
		return (NULL);
	while (i <= size)
	{
		if (i < size - ft_strlen(s2))
		{
			str[i] = *s1++;
		}
		else
		{
			str[i] = *s2++;
		}
		i++;
	}
	str[i] = 0;
	return (str);
}
