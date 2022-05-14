/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:16:39 by aasli             #+#    #+#             */
/*   Updated: 2021/11/29 10:56:04 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int		i;
	char	*tmpd;
	char	*tmps;

	i = (int)n;
	tmpd = (char *)dest;
	tmps = (char *)src;
	if (dest > src)
	{
		i--;
		while (i >= 0)
		{
			tmpd[i] = tmps[i];
			i--;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
