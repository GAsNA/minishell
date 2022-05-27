/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:38:45 by aasli             #+#    #+#             */
/*   Updated: 2022/05/27 19:56:15 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/builtins.h"
#include "../libft/libft.h"

extern int	g_status;

char	**get_c_nv(t_lenv **lenv);
void	ft_redir_pipe(t_cmd *cmd)
{
	if (pipe(cmd->pipe_fd) == -1)
	{
		ft_putstr_fd("Error pipe\n", 1);
		return ;
	}
	if (cmd->next)
	{
		if (cmd->next->fd_in == -1)
			cmd->next->fd_in = cmd->pipe_fd[0];
	}
}

void	ft_prepare_child(t_cmd *tmp)
{
	if (tmp->next)
		close(tmp->pipe_fd[0]);
	if (tmp->fd_in != -1)
	{
		dup2(tmp->fd_in, 0);
		close(tmp->fd_in);
	}
	if (tmp->next != NULL && tmp->fd_out == -1)
	{
		dup2(tmp->pipe_fd[1], 1);
		close(tmp->pipe_fd[1]);
	}
	else if (tmp->fd_out != -1)
	{
		dup2(tmp->fd_out, 1);
		close(tmp->fd_out);
		if (tmp->next)
			close(tmp->pipe_fd[1]);
	}
}

int	no_fork_allowed(char **cmd)
{
	if (ft_strncmp(cmd[0], "cd", ft_strlen("cd\0")) == 0)
		return (1);
	if (ft_strncmp(cmd[0], "unset", ft_strlen("unset\0")) == 0)
		return (1);
	if (ft_strncmp(cmd[0], "exit", ft_strlen("exit\0")) == 0)
		return (1);
	if (ft_strncmp(cmd[0], "export", ft_strlen("export\0")) == 0)
		return (1);
	return (0);
}

int	launch_builtin(t_cmd *cmd, t_lenv **lenv)
{
	if (ft_strncmp(cmd->cmd[0], "cd", ft_strlen("cd\0")) == 0)
		g_status = ft_cd(cmd->cmd, lenv);
	else if (ft_strncmp(cmd->cmd[0], "pwd", ft_strlen("pwd\0")) == 0)
		g_status = ft_pwd(cmd->cmd, lenv);
	else if (ft_strncmp(cmd->cmd[0], "env", ft_strlen("env\0")) == 0)
		g_status = ft_env(cmd->cmd, lenv);
	else if (ft_strncmp(cmd->cmd[0], "unset", ft_strlen("unset\0")) == 0)
		g_status = ft_unset(cmd->cmd, lenv);
	else if (ft_strncmp(cmd->cmd[0], "exit", ft_strlen("exit\0")) == 0)
		g_status = ft_exit(cmd->cmd, lenv);
	else if (ft_strncmp(cmd->cmd[0], "export", ft_strlen("export\0")) == 0)
		g_status = ft_export(cmd->cmd, lenv);
	else if (ft_strncmp(cmd->cmd[0], "echo", ft_strlen("echo\0")) == 0)
		g_status = ft_echo(cmd->cmd, lenv);
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

int	ft_exec_child(t_cmd *cmd, t_lenv **lenv)
{
	if (is_builtin(cmd->cmd))
		launch_builtin(cmd, lenv);
	else
	{
		char **env = get_c_nv(lenv);
		char **paths = ft_get_paths(lenv);
		int  i = 0;
		char *tmp;
		char *path;
		if (!env[0])
			printf("env empty\n");
		execve(cmd->cmd[0], cmd->cmd, env);
		while (paths[i])
		{
			tmp = ft_strjoin(paths[i], "/");
			path = ft_strjoin(tmp, cmd->cmd[0]);
			free(tmp);
			g_status = execve(path, cmd->cmd, env);
			free(path);
			i++;
		}
	}
	//if (cmd->next == NULL)
	//{
		close (0);
		close (1);
		close (2);
//	}
	exit (0);
}

void	ft_loop_cmds(t_cmd *cmds, t_lenv **env)
{
	t_cmd	*tmp;

	tmp = cmds;
	while (tmp != NULL)
	{
		if (tmp->next)
			ft_redir_pipe(tmp);
		if (tmp->next == NULL && no_fork_allowed(tmp->cmd))
			g_status = launch_builtin(tmp, env);
		else
		{
			tmp->pid = fork ();
			if (tmp->pid == 0)
			{
				ft_prepare_child(tmp);
				ft_exec_child(tmp, env);
			}
			else if (tmp->pid != 0)
			{
				if (tmp->next)
					close(tmp->pipe_fd[1]);
				if (tmp->fd_in != -1)
					close(tmp->fd_in);
				if (tmp->fd_out != -1)
					close(tmp->fd_out);
			}
		}
		tmp = tmp->next;
	}
	tmp = cmds;
	while (tmp != NULL)
	{
		if (tmp->pid != 0)
		{
			waitpid(tmp->pid, &g_status, 0);
		}
		tmp = tmp->next;
	}
}
