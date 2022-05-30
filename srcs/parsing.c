/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:28:13 by rleseur           #+#    #+#             */
/*   Updated: 2022/05/30 17:15:44 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_regroup	*get_av(t_regroup *reg, char ***av)
{
	int			i;
	t_regroup	*tmp;

	tmp = reg;
	i = -1;
	while (++i >= 0 && tmp && ft_strcmp(tmp->str, "|") != 0
		&& ft_strcmp(tmp->str, "<") != 0 && ft_strcmp(tmp->str, "<<") != 0
		&& ft_strcmp(tmp->str, ">") != 0 && ft_strcmp(tmp->str, ">>") != 0)
		tmp = tmp->next;
	*av = malloc((i + 1) * sizeof(char *));
	if (!*av)
		return (0);
	i = -1;
	while (reg && ft_strcmp(reg->str, "|") != 0
		&& ft_strcmp(reg->str, "<") != 0 && ft_strcmp(reg->str, "<<") != 0
                && ft_strcmp(reg->str, ">") != 0 && ft_strcmp(reg->str, ">>") != 0)
	{
		(*av)[++i] = reg->str;
		reg = reg->next;
	}
	(*av)[i + 1] = 0;
	return (reg);
}

static int	get_fd_out(t_regroup *reg)
{
	if (reg && ft_strcmp(reg->str, ">") == 0)
		return (open(reg->next->str, O_CREAT | O_TRUNC));
	else if (reg && ft_strcmp(reg->str, ">>") == 0)
		return (open(reg->next->str, O_CREAT | O_APPEND));
	else
		return (-42);
}

static t_regroup	*get_other_av(t_regroup *reg, char ***av)
{
	int		i;
	char		**tmpav;
	t_regroup	*tmp;

	if (!(*av)[0])
	{
		while (reg && ft_strcmp(reg->str, "|") != 0)
			reg = reg->next;
		return (reg);
	}
	if (reg && reg->next && reg->next->next)
		reg = reg->next->next;
	tmp = reg;
	i = 0;
	while ((*av)[i])
		i++;
	while (tmp && ft_strcmp(tmp->str, "|") != 0)
	{
		tmp = tmp->next;
		i++;
	}
	tmpav = *av;
	*av = NULL;
	*av = malloc((i + 1) * sizeof(char *));
	if (!*av)
		return (0);
	i = -1;
	while (tmpav[++i])
		(*av)[i] = tmpav[i];
	while (reg && ft_strcmp(reg->str, "|") != 0)
	{
		(*av)[i] = reg->str;
		reg = reg->next;
		i++;
	}
	(*av)[i] = 0;
	return (reg);
}

t_cmd2	*parsing(t_regroup *reg, t_lenv *lenv)
{
	char		**av;
	int		fd_out;
	t_cmd2		*cmd2;
	t_regroup	*tmp;

	if (!reg)
		return (0);
	(void) lenv;
	tmp = reg;
	av = NULL;
	cmd2 = NULL;
	while (tmp)
	{
		tmp = get_av(tmp, &av);
		fd_out = get_fd_out(tmp);
		tmp = get_other_av(tmp, &av);
		ft_list_push_back_cmd2(&cmd2, av, fd_out);
		av = NULL;
		if (tmp && ft_strcmp(tmp->str, "|") == 0)
			tmp = tmp->next;
	}
	ft_list_clear_reg(reg);
	//pipe = get_cmd_left_to_right(pipe);
	//pipe = get_expands(pipe, lenv);
	return (cmd2);
}
