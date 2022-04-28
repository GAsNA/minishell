/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_lists_lexing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 12:17:38 by rleseur           #+#    #+#             */
/*   Updated: 2022/04/27 14:29:43 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexing	*ft_create_elem_lex(char letter, enum e_type type)
{
	t_lexing	*elem;

	elem = malloc(sizeof(t_lexing));
	if (!elem)
		return (0);
	elem->letter = letter;
	elem->type = type;
	elem->next = NULL;
	return (elem);
}

void	ft_list_push_back_lex(t_lexing **begin_list,
		char letter, enum e_type type)
{
	t_lexing	*list;

	if (*begin_list)
	{
		list = *begin_list;
		while (list->next)
			list = list->next;
		list->next = ft_create_elem_lex(letter, type);
	}
	else
		*begin_list = ft_create_elem_lex(letter, type);
}

void	ft_list_clear_lex(t_lexing *begin_list)
{
	t_lexing	*tmp;

	while (begin_list)
	{
		tmp = begin_list->next;
		free(begin_list);
		begin_list = tmp;
	}
}
