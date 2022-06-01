/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:28:13 by rleseur           #+#    #+#             */
/*   Updated: 2022/06/01 11:41:44 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*get_cmd_and_heredoc(t_regroup *reg)
{
	int		i;
	int		fd;
	t_regroup	*tmp;
	t_cmd		*cmd;
	char		**av;
	
	cmd = NULL;
	av = NULL;
	while (reg)
	{
		fd = -42;
		tmp = reg;
		i = 0;
		while (tmp && ft_strcmp(tmp->str, "|") != 0)
		{
			if (ft_strcmp(tmp->str, "<") == 0
				|| ft_strcmp(tmp->str, "<<") == 0
				|| ft_strcmp(tmp->str, ">") == 0
				|| ft_strcmp(tmp->str, ">>") == 0)
			{
				if (tmp->next && ft_strcmp(tmp->next->str, "|") != 0)
					tmp = tmp->next;
			}
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
			/*if (reg->next && ft_strcmp(reg->str, "<<") == 0 && ft_strcmp(reg->next->str, "EOf") == 0)
				fd = make_heredoc();*/
			if (ft_strcmp(reg->str, "<") == 0
				|| ft_strcmp(reg->str, "<<") == 0
				|| ft_strcmp(reg->str, ">") == 0
				|| ft_strcmp(reg->str, ">>") == 0)
			{
				if (reg->next && ft_strcmp(reg->next->str, "|") != 0)
					reg = reg->next;
			}
			else
				av[++i] = reg->str;
			if (reg)
				reg = reg->next;
		}
		av[i + 1] = 0;
		ft_list_push_back_cmd(&cmd, av, fd);
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
	int	flags;

	flags = -42;
	if (ft_strcmp(reg->str, ">") == 0)
		flags = O_CREAT | O_TRUNC;
	else if (ft_strcmp(reg->str, ">>") == 0)
		flags = O_CREAT | O_APPEND;
	if (!reg->next || ft_strcmp(reg->next->str, "|") == 0)
		return (-42);
	return (open(reg->next->str, flags, 0666));
}

static int	get_fd_in(t_regroup *reg)
{
	int	flags;

	flags = -42;
	if (ft_strcmp(reg->str, "<") == 0)
		flags = O_RDONLY;
	if (!reg->next || ft_strcmp(reg->next->str, "|") == 0)
		return (-42);
	if (any_next_heredoc(reg))
		return (open(reg->next->str, flags));
	else
		return (-21);
}

static t_cmd	*get_in_out_file(t_cmd *cmd, t_regroup *reg)
{
	int	fd;
	t_cmd	*rt;

	rt = cmd;
	while (reg)
	{
		while (reg && ft_strcmp(reg->str, "|") != 0)
		{
			if (ft_strcmp(reg->str, ">") == 0
				|| ft_strcmp(reg->str, ">>") == 0)
			{
				fd = get_fd_out(reg);
				if (fd == -1)
				{
					printf("bash: %s: Permission denied\n", reg->next->str);
					//cmd->cmd = NULL;
					cmd->fd_in = -1;
				}
				else if (fd == -42)
				{
					printf("bash: syntax error near unexpected token ");
					if (!reg->next)
						printf("`newline'\n");
					else
						printf("`|'\n");
				}
				else
					cmd->fd_out = fd;
				reg = reg->next;
			}
			else if ((ft_strcmp(reg->str, "<") == 0
				|| ft_strcmp(reg->str, "<<") == 0))
			{
				fd = get_fd_in(reg);
				if (fd == -1)
				{
					printf("bash: %s: No such file or directory\n", reg->next->str);
					//cmd->cmd = NULL;
					cmd->fd_out = -1;
				}
				else if (fd == -42)
				{
					printf("bash: syntax error near unexpected token ");
					if (!reg->next)
						printf("`newline'\n");
					else
						printf("`|'\n");
				}
				else if (fd != -21)
					cmd->fd_in = fd;
				reg = reg->next;
			}
			if (reg && ft_strcmp(reg->str, "|") != 0)
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
