/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:38:43 by rleseur           #+#    #+#             */
/*   Updated: 2022/04/29 12:00:35 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_quotes(int *quote1, int *quote2)
{
	if (*quote1 == 0 && *quote2 == 0)
		*quote1 = 1;
	else
		*quote1 = 0;
}

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
			set_quotes(&s_quote, &d_quote);
		else if (line[i] == '"')
			set_quotes(&d_quote, &s_quote);
	}
	if (s_quote == 1 || d_quote == 1)
		return (0);
	return (1);
}

static int	has_no_double_pipe(char *line)
{
	int	i;
	int	j;
	
	i = -1;
	while (line[++i])
	{
		if (line[i] == '|')
		{
			j = i + 1;
			while (line[j] == ' ')
				j++;
			if (!line[j] || line[j] == '|')
				return (0);
		}
	}
	return (1);
}

static enum e_type	get_type(char c)
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

	if (!is_quotes_close(line) || !has_no_double_pipe(line))
		return (0);
	lexing = ft_create_elem_lex(line[0], get_type(line[0]));
	if (!lexing)
		return (0);
	i = 0;
	while (line[++i])
		ft_list_push_back_lex(&lexing, line[i], get_type(line[i]));
	return (lexing);
}
