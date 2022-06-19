/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:14:56 by aasli             #+#    #+#             */
/*   Updated: 2022/06/19 15:03:10 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/builtins.h"
#include "../libft/libft.h"

extern int	g_status;

int	ft_prepare_child(t_cmd *tmp)
{
	if (tmp->next)
		close(tmp->pipe_fd[0]);
	if (tmp->fd_in != -1)
	{
		if (dup2(tmp->fd_in, 0) == -1)
			return (write(2, "Dup error\n", ft_strlen("Dup error\n")), 0);
		close(tmp->fd_in);
	}
	if (tmp->next != NULL && tmp->fd_out == -1)
	{
		if (dup2(tmp->pipe_fd[1], 1) == -1)
			return (write(2, "Dup error\n", ft_strlen("Dup error\n")), 0);
		close(tmp->pipe_fd[1]);
	}
	else if (tmp->fd_out != -1)
	{
		if (dup2(tmp->fd_out, 1) == -1)
			return (write(2, "Dup error\n", ft_strlen("Dup error\n")), 0);
		close(tmp->fd_out);
		if (tmp->next)
			close(tmp->pipe_fd[1]);
	}
	return (1);
}

int	no_fork_allowed(char **cmd)
{
	if (cmd[0] == NULL)
		return (0);
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

static void	launch_execve(t_data *data, t_cmd *cmd)
{
	char	**env;
	char	*path;

	env = get_c_nv(&data->env);
	execve(cmd->cmd[0], cmd->cmd, env);
	path = get_exec_path(cmd->cmd[0], data);
	if (path)
		execve(path, cmd->cmd, env);
	free_split(env);
	if (path)
		free(path);
}

int	ft_exec_child(t_cmd *cmd, t_data *data)
{
	char	*str;

	if (*cmd->cmd == NULL || ft_strcmp("", *cmd->cmd) == 0)
	{
	}
	else if (is_builtin(cmd->cmd))
		launch_builtin(cmd, data);
	else if (cmd->cmd[0])
	{
		handle_signals_exec(data);
		launch_execve(data, cmd);
		str = ft_strjoin(cmd->cmd[0], ": command not found\n");
		write(2, str, ft_strlen(str));
		g_status = 127;
		free(str);
	}
	free_all(data, cmd);
	ft_close();
	if (errno == EACCES)
		g_status = 126;
	exit (g_status);
}

void	wait_childs(t_cmd *cmd)
{
	while (cmd != NULL)
	{
		if (cmd->pid != 0)
			waitpid(cmd->pid, &g_status, 0);
		if (WIFEXITED(g_status))
			g_status = WEXITSTATUS(g_status);
		else if (g_status != 131)
			g_status = 130;
		cmd = cmd->next;
	}
}
