/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:28:13 by rleseur           #+#    #+#             */
/*   Updated: 2022/04/19 12:01:53 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// NORME
static int	is_quotes_close(char *line)
{
	int	i;
	int	s_quote;
	int	d_quote;

	s_quote = 0;
	d_quote = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '\'')
		{
			if (s_quote == 0 && d_quote == 0)
				s_quote = 1;
			else
				s_quote = 0;
		}
		else if (line[i] == '"')
		{
			if (d_quote == 0 && s_quote == 0)
				d_quote = 1;
			else
				d_quote = 0;
		}
	}
	if (s_quote == 1 || d_quote == 1)
		return (0);
	return (1);
}

t_lexing	*ft_create_elem(char letter, enum e_type type)
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

void	ft_list_push_back(t_lexing **begin_list, char letter, enum e_type type)
{
	t_lexing	*list;

	if (*begin_list)
	{
		list = *begin_list;
		while (list->next)
			list = list->next;
		list->next = ft_create_elem(letter, type);
	}
	else
		*begin_list = ft_create_elem(letter, type);
}

enum e_type	get_type(char c)
{
	if (c == ' ')
		return (SPACE_);
	else if (c == '>')
		return (OUTREDIR);
	else if (c == '<')
		return (INREDIR);
	else if (c == '|')
		return (PIPE);
	else if (c == '\'')
		return (SIMPLEQUOTE);
	else if (c == '"')
		return (DOUBLEQUOTE);
	else
		return (LITERAL);
}

t_lexing	*get_lexing(char *line)
{
	int			i;
	t_lexing	*lexing;

	lexing = ft_create_elem(line[0], get_type(line[0]));
	if (!lexing)
		return (0);
	i = 0;
	while (line[++i])
		ft_list_push_back(&lexing, line[i], get_type(line[i]));
	return (lexing);
}

t_lexing	*get_commands(char *line)
{
	t_lexing	*lexing;

	if (!is_quotes_close(line))
	{
		printf("C'est pas bon.\n");
		return (0);
	}
	lexing = get_lexing(line);
	return (lexing);
}
