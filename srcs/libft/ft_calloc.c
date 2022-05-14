/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:14:47 by aasli             #+#    #+#             */
/*   Updated: 2021/11/29 13:23:24 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*array;
	size_t	i;

	i = 0;
	array = malloc(nmemb * size);
	if (!array)
		return (NULL);
	while (i < size * nmemb)
	{
		array[i] = 0;
		i++;
	}
	return ((void *)array);
}
