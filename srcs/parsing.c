/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:28:13 by rleseur           #+#    #+#             */
/*   Updated: 2022/05/17 13:17:47 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_regroup	*get_av(t_regroup *reg, char ***av)
{
	int			i;
	t_regroup	*tmp;

	tmp = reg;
	i = 0;
	while (tmp && ft_strcmp(tmp->str, "|") != 0)
	{
		i++;
		tmp = tmp->next;
	}
	*av = malloc((i + 1) * sizeof(char *));
	if (!*av)
		return (0);
	i = -1;
	while (reg && ft_strcmp(reg->str, "|") != 0)
	{
		(*av)[++i] = reg->str;
		reg = reg->next;
	}
	if (reg)
	{
		free(reg->str);
		reg = reg->next;
	}
	(*av)[i + 1] = 0;
	return (reg);
}

static t_pipe	*get_cmd_left_to_right(t_pipe *pipe)
{
	t_pipe	*rt;

	rt = pipe;
	while (pipe->next)
	{
		pipe->right = pipe->next->left;
		pipe = pipe->next;
	}
	return (rt);
}

static t_pipe	*get_redir(t_pipe *pipe)
{
	int		i;
	t_pipe	*rt;

	rt = pipe;
	while (pipe)
	{
		i = -1;
		while (pipe->left->av[++i])
		{
			if (ft_strcmp(pipe->left->av[i], "<") == 0
				|| ft_strcmp(pipe->left->av[i], "<<") == 0)
				ft_list_push_back_redir(&pipe->left->redir,
					pipe->left->av[i], INREDIR);
			else if (ft_strcmp(pipe->left->av[i], ">") == 0
				|| ft_strcmp(pipe->left->av[i], ">>") == 0)
				ft_list_push_back_redir(&pipe->left->redir,
					pipe->left->av[i], OUTREDIR);
		}
		if (!pipe->left->redir)
			pipe->left->redir = ft_create_elem_redir_null();
		pipe = pipe->next;
	}
	return (rt);
}

t_pipe	*parsing(t_regroup *reg, t_lenv *lenv)
{
	char		**av;
	t_pipe		*pipe;
	t_regroup	*tmp;

	if (!reg)
		return (0);
	(void) lenv;
	tmp = reg;
	av = NULL;
	tmp = get_av(tmp, &av);
	pipe = ft_create_elem_pipe(av);
	if (!pipe)
		return (0);
	while (tmp)
	{
		tmp = get_av(tmp, &av);
		ft_list_push_back_pipe(&pipe, av);
		av = NULL;
	}
	ft_list_clear_reg(reg);
	pipe = get_cmd_left_to_right(pipe);
	pipe = get_redir(pipe);
	pipe = get_expands(pipe, lenv);
	return (pipe);
}
