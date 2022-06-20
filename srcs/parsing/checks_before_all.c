/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_before_all.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:00:19 by rleseur           #+#    #+#             */
/*   Updated: 2022/06/20 15:27:03 by rleseur          ###   ########.fr       */
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

int	is_quotes_close(char *line)
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
	if (s_quote == 1)
		return (error_syntax('\''));
	if (d_quote == 1)
		return (error_syntax('"'));
	return (1);
}

int	has_no_double_pipe(char *line)
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
				return (error_syntax(line[j]));
		}
	}
	return (1);
}

static int	check_redir(char *line, int i, int *j)
{
	if (line[i] == '<')
	{
		if (line[*j] == '<')
			(*j)++;
		else if (line[*j] == '>')
			return (0);
	}
	else if (line[i] == '>')
	{
		if (line[*j] == '>')
			(*j)++;
		else if (line[*j] == '<')
			return (0);
	}
	return (1);
}

int	has_no_multiple_redir(char *line)
{
	int	i;
	int	j;
	int	ret;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '<' || line[i] == '>')
		{
			j = i + 1;
			ret = check_redir(line, i, &j);
			if (!ret)
				return (error_syntax(line[j]));
			while (line[j] == ' ')
				j++;
			if (!line[j] || line[j] == '<' || line[j] == '>' || line[j] == '|')
				return (error_syntax(line[j]));
		}
	}
	return (1);
}
