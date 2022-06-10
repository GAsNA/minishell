/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regroup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 13:58:50 by rleseur           #+#    #+#             */
/*   Updated: 2022/06/10 13:43:55 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	determine_type(t_lexing *lex, int *s_quote, int *d_quote)
{
	if (lex->type == SIMPLEQUOTE)
	{
		if (*s_quote == 0 && *d_quote == 0)
			*s_quote = 1;
		else
			*s_quote = 0;
	}
	else if (lex->type == DOUBLEQUOTE)
	{
		if (*d_quote == 0 && *s_quote == 0)
			*d_quote = 1;
		else
			*d_quote = 0;
	}
	else if (lex->type == SPACE_)
	{
		if (*d_quote == 0 && *s_quote == 0)
			return (1);
	}
	return (0);
}

static t_lexing	*choose_str(t_lexing *lex, int *i)
{
	int	s_quote;
	int	d_quote;

	s_quote = 0;
	d_quote = 0;
	while (lex)
	{
		if (determine_type(lex, &s_quote, &d_quote))
		{
			lex = lex->next;
			break ;
		}
		if (lex->next && lex->type != lex->next->type
			&& lex->type != DOUBLEQUOTE && lex->type != SIMPLEQUOTE
			&& lex->next->type != DOUBLEQUOTE && lex->next->type != SIMPLEQUOTE
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
	if (i == 0)
		return (lex);
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
	t_lexing	*tmp;

	if (!lex)
		return (0);
	tmp = lex;
	str = NULL;
	while (!str)
	{
		tmp = ft_regroup(tmp, &str);
		regroup = ft_create_elem_reg(str);
		if (!regroup)
			return (0);
	}
	str = NULL;
	while (tmp)
	{
		tmp = ft_regroup(tmp, &str);
		if (str && str[0])
			ft_list_push_back_reg(&regroup, str);
		str = NULL;
	}
	ft_list_clear_lex(lex);
	return (regroup);
}
