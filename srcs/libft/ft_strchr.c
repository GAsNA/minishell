/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:17:50 by aasli             #+#    #+#             */
/*   Updated: 2021/11/30 15:36:40 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	*tmp;

	tmp = (unsigned char *)s;
	i = -1;
	while (s[++i])
	{
		if ((unsigned char)c == tmp[i])
			return ((char *)tmp + i);
	}
	if (c == '\0')
		return ((char *)tmp + i);
	return (NULL);
}
