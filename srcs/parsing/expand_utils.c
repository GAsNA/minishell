/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:10:43 by rleseur           #+#    #+#             */
/*   Updated: 2022/06/20 12:11:15 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_iden(char c)
{
	if (c == ' ' || c == '\'' || c == '"' || c == '$'
		|| c == ':' || c == ';' || c == '-' || c == '?')
		return (0);
	return (1);
}

int	there_are_expand(char *av)
{
	int	i;

	i = -1;
	while (av[++i])
		if (av[i] == '$' && av[i + 1] && (av[i + 1] == '?'
				|| is_valid_iden(av[i + 1])))
			return (1);
	return (0);
}

int	get_k_n(char *line, int *i, int *inte)
{
	int	n;

	n = 0;
	while (line[++(*i)])
	{
		if ((line[(*i)] == '$' && line[(*i) + 1]
				&& is_valid_iden(line[(*i) + 1]) && n == 0) || n > 0)
		{
			if ((!line[(*i)] || !is_valid_iden(line[(*i)])) && n > 0)
				break ;
			n++;
		}
		else if (line[(*i)] == '$' && line[(*i) + 1] == '?')
		{
			*inte = 1;
			break ;
		}
	}
	return (n - 1);
}
