/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strgdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:18:03 by aasli             #+#    #+#             */
/*   Updated: 2022/06/06 12:33:30 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"

char	*ft_strgdup(t_glist **lst, const char *s)
{
	char		*cpy;
	int			size;
	int			i;

	size = strlen(s) + 1;
	cpy = (char *) ft_malloc(sizeof(char), size, lst);
	if (!(cpy))
		return (0);
	i = 0;
	while (s[i])
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
