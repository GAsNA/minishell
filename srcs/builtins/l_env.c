/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 11:09:39 by aasli             #+#    #+#             */
/*   Updated: 2022/04/28 17:56:02 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../libft/libft.h"

t_lenv	*ft_last_lenv(t_lenv **begin)
{
	t_lenv	*tmp;

	tmp = *begin;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

int	ft_addback_lenv(t_lenv **begin, t_lenv *new)
{
	t_lenv	*last;

	if (*begin == NULL)
		*begin = new;
	else
	{
		last = ft_last_lenv(begin);
		if (!last)
			return (0);
		last->next = new;
	}
	return (1);
}

t_lenv	*ft_new_lenv(char *line)
{
	t_lenv	*new;
	int		n;

	new = malloc(sizeof(t_lenv) * 1);
	if (!new)
		return (NULL);
	n = ft_strnlen(line) + 1;
	new->k = ft_substr(line, 0, n);
	if (!new->k)
	{
		free (new);
		return (NULL);
	}
	new->v = ft_strdup(line + n);
	if (!new->v)
	{
		free (new);
		free (new->k);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}
