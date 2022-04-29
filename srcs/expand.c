/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 16:13:02 by rleseur           #+#    #+#             */
/*   Updated: 2022/04/29 16:13:50 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*make_expand(char *str, int n, t_lenv *lenv)
{
	int		i;
	int		j;
	char	*n_str;

	i = -1;
	while (str[++i])
		if (str[i] == '$')
			break ;
	while (lenv)
	{
		if (ft_strncmp(&str[i + 1], lenv->k, n) == 0)
			break ;
		lenv = lenv->next;
	}
	if (!lenv)
		return (str);
	n_str = malloc((ft_strlen(str) - (n + 1)
				+ ft_strlen(lenv->v) + 1) * sizeof(char));
	if (!n_str)
		return (0);
	i = -1;
	while (str[++i] && str[i] != '$')
		n_str[i] = str[i];
	j = -1;
	while (lenv->v[++j])
		n_str[i + j] = lenv->v[j];
	i += n;
	while (str[++i])
	{
		n_str[i + j - (n + 1)] = str[i];
	}
	n_str[i + j] = '\0';
	return (n_str);
}

t_pipe	*get_expands(t_pipe *pipe, t_lenv *lenv)
{
	int		i;
	int		j;
	int		k;
	int		s_quote;
	t_pipe	*rt;

	rt = pipe;
	while (pipe)
	{
		s_quote = 0;
		i = -1;
		while (pipe->left->av[++i])
		{
			if (pipe->left->av[i][0] == '\'')
				s_quote = 1;
			j = -1;
			k = 0;
			while (pipe->left->av[i][++j])
			{
				if (pipe->left->av[i][j] == '$' && s_quote == 0 && k == 0)
					k++;
				if ((pipe->left->av[i][j] == ' ' || pipe->left->av[i][j] == '\''
							|| pipe->left->av[i][j] == '"') && k > 0)
					break ;
				if (k > 0)
					k++;
			}
			if (k > 0)
				pipe->left->av[i] = make_expand(pipe->left->av[i], k - 2, lenv);
		}
		pipe = pipe->next;
	}
	return (rt);
}
