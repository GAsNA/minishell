/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:18:19 by aasli             #+#    #+#             */
/*   Updated: 2021/11/29 12:48:44 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (*dest && i < size)
	{
		dest++;
		i++;
	}
	while (*src && i + 1 < size)
	{
		*dest = *src;
		i++;
		dest++;
		src++;
	}
	if (i < size)
		*dest = '\0';
	while (*src)
	{
		src++;
		i++;
	}
	return (i);
}
