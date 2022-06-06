/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:49:24 by aasli             #+#    #+#             */
/*   Updated: 2022/06/06 13:45:11 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"

static int	ft_isset(char c, char set)
{
	if (set == c)
		return (1);
	return (0);
}

static int	ft_strlen_split(const char *str, int index, char set)
{
	int	i;

	i = 0;
	while (str[index] && !(ft_isset(str[index], set)))
	{
		index++;
		i++;
	}
	return (i);
}

static int	ft_count_str(const char *str, char set)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (ft_isset(str[i], set) && str[i])
			i++;
		if (str[i] != '\0')
			count++;
		while (!(ft_isset(str[i], set)) && str[i])
			i++;
	}
	return (count);
}

static	char	**ft_free(char **splitted, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
	return (NULL);
}

char	**ft_gsplit(t_glist **lst, const char *s, char c)
{
	int				i;
	unsigned int	j;
	int				countstr;
	char			**strsplitted;

	if (!s)
		return (NULL);
	countstr = ft_count_str(s, c) + 1;
	strsplitted = (char **) ft_malloc((size_t) sizeof(char *),
			(size_t) countstr, lst);
	if (!strsplitted)
		return (0);
	i = 0;
	j = 0;
	while (i < countstr - 1)
	{
		while (ft_isset(s[j], c))
			j++;
		strsplitted[i] = ft_subgstr(lst, s, j,
				(size_t) ft_strlen_split(s, j, c));
		j += ft_strlen_split(s, j, c) + 1;
		i++;
	}
	strsplitted[i] = 0;
	return (strsplitted);
}
