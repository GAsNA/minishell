/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:28:13 by rleseur           #+#    #+#             */
/*   Updated: 2022/04/26 17:10:39 by rleseur          ###   ########.fr       */
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
	return (pipe);
}
