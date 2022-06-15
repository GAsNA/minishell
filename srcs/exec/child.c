/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:14:56 by aasli             #+#    #+#             */
/*   Updated: 2022/06/15 14:21:36 by aasli            ###   ########.fr       */
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

int	ft_exec_child(t_cmd *cmd, t_data *data)
{
	char	*path;
	char	**env;

	if (*cmd->cmd == NULL)
	{
	}
	else if (is_builtin(cmd->cmd))
		launch_builtin(cmd, data);
	else if (cmd->cmd[0])
	{
		env = get_c_nv(&data->env);
		path = get_exec_path(cmd->cmd[0], data);
		if (path)
			execve(path, cmd->cmd, env);
		free_split(env);
		free(path);
		path = ft_strjoin(cmd->cmd[0], ": command not found\n");
		write(2, path, ft_strlen(path));
		g_status = 127;
		free(path);
	}
	ft_list_clear_cmd(cmd);
	free_lenv(&data->env);
	free(data->line);
	ft_close();
	if (errno == EACCES)
		exit (126);
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
		cmd = cmd->next;
	}
}
