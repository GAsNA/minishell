/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 16:13:02 by rleseur           #+#    #+#             */
/*   Updated: 2022/05/04 11:57:10 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_expand(char *str, int n, t_lenv *lenv)
{
	int		i;
	int		j;
	char	*n_str;

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
		n_str[i + j - (n + 1)] = str[i];
	n_str[i + j - (n + 1)] = '\0';
	return (n_str);
}

static char	*make_expand(char *str, int n, t_lenv *lenv)
{
	int		i;
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
	n_str = replace_expand(str, n, lenv);
	return (n_str);
}

static void	prepare_expand(char	**av, t_lenv *lenv)
{
	int	i;
	int	k;
	int	s_quote;

	s_quote = 0;
	if ((*av)[0] == '\'')
		s_quote = 1;
	i = -1;
	k = 0;
	while ((*av)[++i])
	{
		if ((*av)[i] == '$' && s_quote == 0 && k == 0)
			k++;
		if (((*av)[i] == ' ' || (*av)[i] == '\''
					|| (*av)[i] == '"') && k > 0)
			break ;
		if (k > 0)
			k++;
	}
	if (k > 0)
		*av = make_expand(*av, k - 2, lenv);
}

t_pipe	*get_expands(t_pipe *pipe, t_lenv *lenv)
{
	int		i;
	t_pipe	*rt;

	rt = pipe;
	while (pipe)
	{
		i = -1;
		while (pipe->left->av[++i])
			prepare_expand(&pipe->left->av[i], lenv);
		pipe = pipe->next;
	}
	return (rt);
}
