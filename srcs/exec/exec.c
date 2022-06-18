/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:38:45 by aasli             #+#    #+#             */
/*   Updated: 2022/06/18 13:29:16 by aasli            ###   ########.fr       */
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

int	launch_builtin(t_cmd *cmd, t_data *data)
{
	if (ft_strncmp(cmd->cmd[0], "cd", ft_strlen("cd\0")) == 0)
		g_status = ft_cd(cmd->cmd, &data->env);
	else if (ft_strncmp(cmd->cmd[0], "pwd", ft_strlen("pwd\0")) == 0)
		g_status = ft_pwd(cmd->cmd, &data->env);
	else if (ft_strncmp(cmd->cmd[0], "env", ft_strlen("env\0")) == 0)
		g_status = ft_env(cmd->cmd, &data->env);
	else if (ft_strncmp(cmd->cmd[0], "unset", ft_strlen("unset\0")) == 0)
		g_status = ft_unset(cmd->cmd, &data->env);
	else if (ft_strncmp(cmd->cmd[0], "exit", ft_strlen("exit\0")) == 0)
		g_status = ft_exit(cmd->cmd, &data->env);
	else if (ft_strncmp(cmd->cmd[0], "export", ft_strlen("export\0")) == 0)
		g_status = ft_export(cmd->cmd, data);
	else if (ft_strncmp(cmd->cmd[0], "echo", ft_strlen("echo\0")) == 0)
		g_status = ft_echo(cmd->cmd, &data->env);
	if (cmd->next)
		close(cmd->pipe_fd[0]);
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
	if (ft_strncmp(cmd[0], "cd", ft_strlen("cd\0")) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "pwd", ft_strlen("pwd\0")) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "env", ft_strlen("env\0")) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "unset", ft_strlen("unset\0")) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "exit", ft_strlen("exit\0")) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "export", ft_strlen("export\0")) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "echo", ft_strlen("echo\0")) == 0)
		return (1);
	return (0);
}

int	ft_fork(t_cmd *cmds, t_cmd *tmp, t_data *data)
{
	tmp->pid = fork ();
	if (tmp->pid == -1)
	{
		ft_list_clear_cmd(cmds);
		return (0);
	}
	handle_signals_exec(data);
	if (tmp->pid == 0)
	{
		if (ft_prepare_child(tmp) == 0)
		{
			ft_list_clear_cmd(cmds);
			return (0);
		}
		ft_exec_child(tmp, data);
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
		if (tmp->next == NULL && no_fork_allowed(tmp->cmd) == 1)
			launch_builtin(tmp, data);
		else
		{
			if (ft_fork(cmds, tmp, data) == 0)
				return ;
		}
		tmp = tmp->next;
	}
	tmp = cmds;
	wait_childs(tmp);
	
}
