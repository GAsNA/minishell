/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:38:45 by aasli             #+#    #+#             */
/*   Updated: 2022/06/22 15:39:01 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/builtins.h"
#include "../libft/libft.h"

extern int	g_status;

int	ft_redir_pipe(t_cmd *cmd)
{
	if (pipe(cmd->pipe_fd) == -1)
	{
		ft_putstr_fd("Error pipe\n", 1);
		return (0);
	}
	if (cmd->next)
	{
		if (cmd->next->fd_in == -1)
			cmd->next->fd_in = cmd->pipe_fd[0];
	}
	return (1);
}

int	launch_builtin(t_cmd *cmd, t_data *data, t_cmd *cmds, int fork)
{
	int fd2 = dup(0);
	int fd3 = dup(1);
	
	if (cmd->fd_in != -1)
	{
		printf("redir in\n");
		dup2(cmd->fd_in, 0);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != -1)
	{
		printf("redir out\n");
		dup2(cmd->fd_out, 1);
		close(0);
		close(cmd->fd_out);
	}
	if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		g_status = ft_cd(cmd->cmd, &data->env);
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		g_status = ft_pwd(cmd->cmd, &data->env);
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		g_status = ft_env(cmd->cmd, &data->env);
	else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		g_status = ft_unset(cmd->cmd, &data->env);
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
		g_status = ft_exit(cmd->cmd, data, cmds, fork);
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		g_status = ft_export(cmd->cmd, data);
	else if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		g_status = ft_echo(cmd->cmd, &data->env);
	if (cmd->next)
		close(cmd->pipe_fd[0]);
	if (!cmd->next && !cmd->prev)
	{
		dup2(fd2, 0);
		close(fd2);
		dup2(fd3, 1);
		close(fd3);
	}
	if (cmd->fd_in != -1)
		close(cmd->fd_in);
	if (cmd->fd_out != -1)
		close(cmd->fd_out);
	return (0);
}

int	is_builtin(char **cmd)
{
	if (cmd[0] == NULL)
		return (0);
	if (ft_strcmp(cmd[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		return (1);
	return (0);
}

int	ft_fork(t_cmd *cmds, t_cmd *tmp, t_data *data)
{
	tmp->pid = fork ();
	reset_signals(data);
	if (tmp->pid == -1)
	{
		ft_list_clear_cmd(cmds);
		return (0);
	}
	if (tmp->pid == 0)
	{
		if (ft_prepare_child(tmp) == 0)
		{
			ft_list_clear_cmd(cmds);
			return (0);
		}
		ft_exec_child(cmds, tmp, data);
	}
	else if (tmp->pid != 0)
		close_parent_fds(tmp);
	return (1);
}

void	ft_loop_cmds(t_cmd *cmds, t_data *data)
{
	t_cmd	*tmp;

	tmp = cmds;
	while (tmp != NULL)
	{
		if (tmp->next)
		{
			if (!ft_redir_pipe(tmp))
			{
				ft_list_clear_cmd(cmds);
				return ;
			}
		}
		if (tmp->prev == NULL && tmp->next == NULL && is_builtin(tmp->cmd) == 1)
			launch_builtin(tmp, data, cmds, 0);
		else
			if (ft_fork(cmds, tmp, data) == 0)
				return ;
		tmp = tmp->next;
	}
	tmp = cmds;
	wait_childs(tmp);
}
