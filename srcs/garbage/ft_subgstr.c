/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:54:53 by aasli             #+#    #+#             */
/*   Updated: 2022/06/06 13:45:40 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"

char	*ft_subgstr(t_glist **lst, char const *s,
		unsigned int start, size_t len)
{
	char	*new;
	size_t	i;

	if (!s)
		return (NULL);
	if (start > strlen(s))
		return (ft_strgdup(lst, ""));
	i = 0;
	if (len > strlen(s) - start)
		len = strlen(s) - start;
	new = (char *)ft_malloc(sizeof(char), len + 1, lst);
	if (!new)
		return (NULL);
	while (i < len)
	{
		new[i] = s[start + i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
