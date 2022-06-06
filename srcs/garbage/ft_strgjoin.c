/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:09:09 by aasli             #+#    #+#             */
/*   Updated: 2022/06/06 13:50:38 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"

static char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i])
	{
		i++;
	}
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*ft_strgjoin(t_glist **lst, char const *s1, char const *s2)
{
	char	*new;

	new = (char *)ft_malloc((size_t) sizeof(char),
			(size_t)(strlen(s1) + strlen(s2) + 1), lst);
	if (!new)
		return (NULL);
	*new = 0;
	ft_strcat(new, (char *)s1);
	ft_strcat(new, (char *)s2);
	return (new);
}
