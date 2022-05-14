/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:19:41 by aasli             #+#    #+#             */
/*   Updated: 2021/11/30 08:53:07 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	*tmp;

	tmp = (unsigned char *)s;
	i = 0;
	while (tmp[i])
		i++;
	if (c == '\0')
		return ((char *)tmp + i);
	i--;
	while (i >= 0)
	{
		if ((unsigned char)c == s[i])
			return ((char *)tmp + i);
		i--;
	}
	return (NULL);
}
