/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:28:13 by rleseur           #+#    #+#             */
/*   Updated: 2022/04/12 13:55:26 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_command	*get_commands(char *line)
{
	(void) line;
	// Check si quotes fermees
	// Separer all words (except "" et '')
	if (!is_quotes_close(line))
		printf("C'est pas bon.\n");
	return (0);
}
