/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:28:13 by rleseur           #+#    #+#             */
/*   Updated: 2022/06/06 14:03:59 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*get_cmd_and_heredoc(t_regroup *reg)
{
	int			fd;
	t_cmd		*cmd;
	char		**av;

	cmd = NULL;
	av = NULL;
	while (reg)
	{
		fd = -42;
		av = malloc((calcul_av(reg) + 1) * sizeof(char *));
		if (!av)
			return (0);
		reg = divide_cmd(reg, &av, &fd);
		ft_list_push_back_cmd(&cmd, av, fd);
		av = NULL;
		if (reg)
			reg = reg->next;
	}	
	return (cmd);
}

static t_cmd	*get_in_out_file(t_cmd *cmd, t_regroup *reg)
{
	t_cmd	*rt;

	rt = cmd;
	while (reg)
	{
		while (reg && ft_strcmp(reg->str, "|") != 0)
		{
			if (ft_strcmp(reg->str, ">") == 0 || ft_strcmp(reg->str, ">>") == 0)
			{
				check_fd_out(&cmd->fd_in, &cmd->fd_out, reg, &cmd->cmd);
				reg = reg->next;
			}
			else if (ft_strcmp(reg->str, "<") == 0)
			{
				check_fd_in(&cmd->fd_in, &cmd->fd_out, reg, &cmd->cmd);
				reg = reg->next;
			}
			if (reg && ft_strcmp(reg->str, "|") != 0)
				reg = reg->next;
		}
		if (reg)
		{
			free(reg->str);
			reg = reg->next;
		}
		cmd = cmd->next;
	}
	return (rt);
}

static t_cmd	*get_cmd_prev(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp->next)
	{
		tmp->next->prev = tmp;
		tmp = tmp->next;
	}
	return (cmd);
}

t_cmd	*parsing(t_regroup *reg, t_lenv *lenv)
{
	t_cmd		*cmd;

	if (!reg)
		return (0);
	cmd = get_cmd_and_heredoc(reg);
	cmd = get_in_out_file(cmd, reg);
	cmd = get_cmd_prev(cmd);
	cmd = get_expands(cmd, lenv);
	ft_list_clear_reg(reg);
	return (cmd);
}
