/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 14:49:50 by anggonza          #+#    #+#             */
/*   Updated: 2021/11/02 16:42:47 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strndup(char *s, int i, int n)
{
	char	*str;
	int		j;
	int		size;

	if (!s)
		return (NULL);
	size = (ft_strlen(s) + 2) - (i - ((n + i) - ft_strlen(s)));
	str = malloc(size);
	s = (s + i);
	j = 0;
	if (!str)
		return (NULL);
	while (j < size - 1)
	{
		str[j] = s[j];
		j++;
	}
	str[j] = 0;
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 || !set)
		return (ft_strdup(""));
	i = 0;
	j = ft_strlen((const char *)s1) - 1;
	while (ft_strchr(set, s1[i]) != NULL)
		i++;
	while (ft_strchr(set, s1[j]) != NULL)
		j--;
	if (ft_strlen(s1) <= (size_t)i)
		return (ft_strdup(""));
	str = ft_strndup((char *)s1, i, j - i);
	if (!str)
		return (NULL);
	return (str);
}
