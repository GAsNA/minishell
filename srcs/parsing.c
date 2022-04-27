/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:28:13 by rleseur           #+#    #+#             */
/*   Updated: 2022/04/27 11:03:32 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		reg = reg->next;
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
			if (ft_strcmp(pipe->left->av[i], "<") == 0 || ft_strcmp(pipe->left->av[i], "<<") == 0)
				ft_list_push_back_redir(&pipe->left->redir, pipe->left->av[i], INREDIR);
			else if (ft_strcmp(pipe->left->av[i], ">") == 0 || ft_strcmp(pipe->left->av[i], ">>") == 0)
				ft_list_push_back_redir(&pipe->left->redir, pipe->left->av[i], OUTREDIR);
		}
		if (!pipe->left->redir)
		{
			pipe->left->redir = malloc(sizeof(t_redir));
			if (!pipe->left->redir)
				return (0);
			pipe->left->redir->val = NULL;
			pipe->left->redir->next = NULL;
		}	
		pipe = pipe->next;
	}
	return (rt);
}

t_pipe	*parsing(t_regroup *reg)
{
	char	**av;
	t_pipe	*pipe;

	av = NULL;
	reg = get_av(reg, &av);
	pipe = ft_create_elem_pipe(av);
	if (!pipe)
		return (0);
	while (reg)
	{
		reg = get_av(reg, &av);
		ft_list_push_back_pipe(&pipe, av);
		av = NULL;
	}
	pipe = get_cmd_left_to_right(pipe);
	pipe = get_redir(pipe);
	return (pipe);
}
