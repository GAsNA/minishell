/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:28:13 by rleseur           #+#    #+#             */
/*   Updated: 2022/06/20 12:07:19 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*get_cmd_and_heredoc(t_regroup *reg, t_lenv *lenv)
{
	int			fd;
	t_cmd		*cmd;
	char		**av;

	cmd = NULL;
	av = NULL;
	while (reg)
	{
		fd = -1;
		av = malloc((calcul_av(reg) + 1) * sizeof(char *));
		if (!av)
			return (0);
		reg = divide_cmd(reg, &av, &fd, lenv);
		ft_list_push_back_cmd(&cmd, av, fd);
		av = NULL;
		if (reg)
			reg = reg->next;
	}
	return (cmd);
}

static t_regroup	*free_and_pass(t_regroup *reg, int redir)
{
	if (reg && ft_strcmp(reg->str, "|") != 0)
	{
		if (redir)
			free(reg->str);
		if (!redir && ft_strcmp(reg->str, "<<") == 0)
		{
			free(reg->str);
			if (reg->next && ft_strcmp(reg->next->str, "|") != 0)
			{
				free(reg->next->str);
				reg = reg->next;
			}
		}
		reg = reg->next;
	}
	return (reg);
}

static t_regroup	*make_redir(t_regroup *reg, int *fd_in, int *fd_out,
								int *to_free)
{
	int	redir;

	while (reg && reg->str && ft_strcmp(reg->str, "|") != 0
		&& *to_free == 0)
	{
		redir = 0;
		if (ft_strcmp(reg->str, ">") == 0 || ft_strcmp(reg->str, ">>") == 0)
		{
			check_fd_out(fd_in, fd_out, reg, to_free);
			free(reg->str);
			redir = 1;
			reg = reg->next;
		}
		else if (ft_strcmp(reg->str, "<") == 0)
		{
			check_fd_in(fd_in, fd_out, reg, to_free);
			free(reg->str);
			redir = 1;
			reg = reg->next;
		}
		reg = free_and_pass(reg, redir);
	}
	return (reg);
}

static t_cmd	*get_in_out_file(t_cmd *cmd, t_regroup *reg)
{
	t_cmd	*rt;

	rt = cmd;
	while (reg && cmd)
	{
		reg = make_redir(reg, &cmd->fd_in, &cmd->fd_out, &cmd->to_free);
		if (cmd->to_free == 1)
		{
			while (reg && ft_strcmp(reg->str, "|") != 0)
			{
				free(reg->str);
				reg = reg->next;
			}
			free(cmd->cmd);
			cmd->cmd = NULL;
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

static int	get_quotes(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == '\'' || s[i] == '"')
			return (1);
	return (0);
}

static int	get_size(char **cmd)
{
	int		i;
	int		j;
	int		size;
	char	**split;

	size = 0;
	i = -1;
	while (cmd[++i])
	{
		if (get_quotes(cmd[i]))
			size++;
		else
		{
			split = ft_split(cmd[i], ' ');
			j = -1;
			while (split[++j])
				size++;
		}
	}
	return (size);
}

static char	**get_cmd_after_split(char **cmd)
{
	int		i;
	int		j;
	int		k;
	char	**split;
	char	**new_cmd;

	new_cmd = malloc((get_size(cmd) + 1) * sizeof(char *));
	if (!new_cmd)
		return (0);
	i = -1;
	j = -1;
	while (cmd[++i])
	{
		if (get_quotes(cmd[i]))
			new_cmd[++j] = ft_strdup(cmd[i]);
		else
		{
			split = ft_split(cmd[i], ' ');
			k = -1;
			while (split[++k])
				new_cmd[++j] = split[k];
		}
	}
	new_cmd[j + 1] = 0;
	return (new_cmd);
}

static t_cmd	*last_splits(t_cmd *cmd)
{
	int		i;
	char	**tmp_char;
	t_cmd	*ret;

	ret = cmd;
	while (cmd)
	{
		i = -1;
		tmp_char = get_cmd_after_split(cmd->cmd);
		i = -1;
		while (cmd->cmd[++i])
			free(cmd->cmd[i]);
		free(cmd->cmd);
		cmd->cmd = tmp_char;
		cmd = cmd->next;
	}
	return (ret);
}

t_cmd	*parsing(t_regroup *reg, t_lenv *lenv)
{
	t_cmd	*cmd;
	t_cmd	*tmp;

	if (!reg)
		return (0);
	cmd = get_cmd_and_heredoc(reg, lenv);
	cmd = get_in_out_file(cmd, reg);
	tmp = cmd;
	while (tmp->next)
	{
		tmp->next->prev = tmp;
		tmp = tmp->next;
	}
	cmd = get_expands(cmd, lenv);
	cmd = last_splits(cmd);
	cmd = supp_useless_quotes(cmd);
	ft_list_clear_reg(reg);
	return (cmd);
}
