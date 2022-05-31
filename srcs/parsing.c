/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:28:13 by rleseur           #+#    #+#             */
/*   Updated: 2022/05/31 15:42:24 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*get_cmd_and_heredoc(t_regroup *reg)
{
	int		i;
	t_regroup	*tmp;
	t_cmd		*cmd;
	char		**av;
	
	cmd = NULL;
	av = NULL;
	while (reg)
	{
		tmp = reg;
		i = 0;
		while (tmp && ft_strcmp(tmp->str, "|") != 0)
		{
			if (ft_strcmp(tmp->str, "<") == 0
				|| ft_strcmp(tmp->str, "<<") == 0
				|| ft_strcmp(tmp->str, ">") == 0
				|| ft_strcmp(tmp->str, ">>") == 0)
				tmp = tmp->next;
			else
				i++;
			if (tmp)
				tmp = tmp->next;
		}
		av = malloc((i + 1) * sizeof(char *));
		if (!av)
			return (0);
		i = -1;
		while (reg && ft_strcmp(reg->str, "|") != 0)
		{
			if (ft_strcmp(reg->str, "<") == 0
				|| ft_strcmp(reg->str, "<<") == 0
				|| ft_strcmp(reg->str, ">") == 0
				|| ft_strcmp(reg->str, ">>") == 0)
				reg = reg->next;
			else
				av[++i] = reg->str;
			if (reg)
				reg = reg->next;
		}
		av[i + 1] = 0;
		ft_list_push_back_cmd(&cmd, av);
		av = NULL;
		if (reg)
			reg = reg->next;
	}	
	return (cmd);
}

int	any_next_heredoc(t_regroup *reg)
{
	while (reg && ft_strcmp(reg->str, "|") != 0)
	{
		if (reg->next && ft_strcmp(reg->str, "<<") == 0 && ft_strcmp(reg->next->str, "EOF") == 0)
			return (0);
		reg = reg->next;
	}
	return (1);
}

static int	get_fd_out(t_regroup *reg)
{
	int	fd;
	int	flags;

	fd = -42;
	if (reg && ft_strcmp(reg->str, ">") == 0)
		flags = O_CREAT | O_TRUNC;
	else if (reg && ft_strcmp(reg->str, ">>") == 0)
		flags = O_CREAT | O_APPEND;
	else
		flags = -42;
	if (flags != -42)
		fd = open(reg->next->str, flags, 0666);
	return (fd);
}

static int	get_fd_in(t_regroup *reg)
{
	int	fd;
	int	flags;

	fd = -42;
	if (reg && ft_strcmp(reg->str, "<") == 0)
		flags = O_RDONLY;
	else
		flags = -42;
	if (flags != -42)
		fd = open(reg->next->str, flags);
	if (any_next_heredoc(reg))
		return (fd);
	else
		return (-42);
}

static t_cmd	*get_in_out_file(t_cmd *cmd, t_regroup *reg)
{
	t_cmd	*rt;

	rt = cmd;
	while (reg)
	{
		while (reg && ft_strcmp(reg->str, "|") != 0)
		{
			if (ft_strcmp(reg->str, ">") == 0
				|| ft_strcmp(reg->str, ">>") == 0)
			{
				cmd->fd_out = get_fd_out(reg);
				if (cmd->fd_out == -1)
				{
					printf("bash: %s: Permission denied\n", reg->next->str);
					//cmd->cmd = NULL;
					cmd->fd_in = -1;
				}
				reg = reg->next;
			}
			else if ((ft_strcmp(reg->str, "<") == 0
				|| ft_strcmp(reg->str, "<<") == 0))
			{
				cmd->fd_in = get_fd_in(reg);
				// check access
				if (cmd->fd_in == -1)
				{
					printf("bash: %s: No such file or directory\n", reg->next->str);
					//cmd->cmd = NULL;
					cmd->fd_out = -1;
				}
				reg = reg->next;
			}
			if (reg)
				reg = reg->next;
		}
		if (reg)
			reg = reg->next;
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
