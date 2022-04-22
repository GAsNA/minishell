/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:38:43 by rleseur           #+#    #+#             */
/*   Updated: 2022/04/22 13:44:49 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	if (!is_quotes_close(line))
	{
		printf("C'est pas bon.\n");
		return (0);
	}
	lexing = ft_create_elem_lex(line[0], get_type(line[0]));
	if (!lexing)
		return (0);
	i = 0;
	while (line[++i])
		ft_list_push_back_lex(&lexing, line[i], get_type(line[i]));
	return (lexing);
}

static t_lexing	*choose_str(t_lexing *lex, int *i)
{
	int	s_quote;
	int	d_quote;

	s_quote = 0;
	d_quote = 0;
	while (lex)
	{
		if (lex->type == SIMPLEQUOTE)
		{
			if (s_quote == 0 && d_quote == 0)
				s_quote = 1;
			else
				s_quote = 0;
		}
		else if (lex->type == DOUBLEQUOTE)
		{
			if (d_quote == 0 && s_quote == 0)
				d_quote = 1;
			else
				d_quote = 0;
		}
		else if (lex->type == SPACE_)
		{
			if (d_quote == 0 && s_quote == 0)
			{
				lex = lex->next;
				break ;
			}
		}
		if (lex->next && lex->type != lex->next->type
			&& lex->next->type != SPACE_ && d_quote == 0 && s_quote == 0)
		{
			(*i)++;
			lex = lex->next;
			break ;
		}
		(*i)++;
		lex = lex->next;
	}
	return (lex);
}

static t_lexing	*ft_regroup(t_lexing *lex, char **str)
{
	int			i;
	int			j;
	t_lexing	*tmp;

	tmp = lex;
	i = 0;
	lex = choose_str(lex, &i);
	*str = malloc((i + 1) * sizeof(char));
	if (!*str)
		return (0);
	j = -1;
	while (++j < i)
	{
		(*str)[j] = tmp->letter;
		tmp = tmp->next;
	}
	(*str)[j] = '\0';
	return (lex);
}

t_regroup	*get_regroup(t_lexing *lex)
{
	char		*str;
	t_regroup	*regroup;

	if (!lex)
		return (0);
	str = NULL;
	lex = ft_regroup(lex, &str);
	regroup = ft_create_elem_reg(str);
	if (!regroup)
		return (0);
	while (lex)
	{
		lex = ft_regroup(lex, &str);
		ft_list_push_back_reg(&regroup, str);
	}
	return (regroup);
}
