/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:09:09 by aasli             #+#    #+#             */
/*   Updated: 2022/06/19 15:08:22 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

char	*ft_strdjoin(char const *s1, char const *s2, char const *s3)
{
	char	*new;

	if (!s1 || !s2 || !s3)
		return (NULL);
	new = (char *)malloc(((ft_strlen(s1) + ft_strlen(s2)
					+ ft_strlen(s3) + 1) * sizeof (char)));
	if (!new)
		return (NULL);
	*new = 0;
	ft_strcat(new, (char *)s1);
	ft_strcat(new, (char *)s2);
	ft_strcat(new, (char *)s3);
	return (new);
}
