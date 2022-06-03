/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 10:47:48 by anggonza          #+#    #+#             */
/*   Updated: 2021/11/03 12:01:06 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strndup(char *s, int n)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)malloc(n + 1);
	while (i <= n)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

static int	ft_countwords(char *str, char sep)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (str[i])
	{
		if (str[i] != sep && str[i + 1] == sep)
			result++;
		else if (str[i] != sep && str[i + 1] == '\0')
			result++;
		i++;
	}
	return (result);
}

static char	*ft_strtrunk(char *s, char c)
{
	char	*tmp;

	tmp = malloc(2);
	if (!tmp)
		return (NULL);
	tmp[0] = c;
	tmp[1] = '0';
	s = ft_strtrim(s, (const char *)tmp);
	if (!s)
		return (NULL);
	free(tmp);
	return (s);
}

static char	*ft_init_vars(t_vars *v, const char *s, char c)
{
	v->i = 0;
	v->j = 0;
	v->index = 0;
	v->str = ft_strtrunk((char *)s, c);
	if (!v->str)
	{
		free(v->str);
		return (NULL);
	}
	return (v->str);
}

char	**ft_split(char const *s, char c)
{
	t_vars	v;

	if (!s)
		return (NULL);
	if (!ft_init_vars(&v, s, c))
		return (NULL);
	v.result = malloc(sizeof(char *) * ft_countwords((char *)v.str, c) + 1);
	if (!v.result)
		return (NULL);
	while (v.str[v.i] != '\0' && (v.index < ft_countwords((char *)v.str, c)))
	{
		if (v.str[v.i] == c)
		{
			v.i++;
			continue ;
		}
		v.j = v.i + 1;
		while (v.str[v.j] != c && v.str[v.j] != '\0')
			v.j++;
		v.result[v.index++] = ft_strndup((char *)(v.str + v.i), v.j - v.i - 1);
		v.i = v.j;
	}
	free(v.str);
	v.result[v.index] = 0;
	return (v.result);
}
