/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:38:45 by aasli             #+#    #+#             */
/*   Updated: 2022/06/13 08:50:24 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/builtins.h"
#include "../libft/libft.h"

extern int	g_status;

char	**get_c_nv(t_lenv **lenv);

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

char	*try_access_path(char *cmd, char **paths, int i)
{
	char	*path;
	char	*tmp;

	tmp = ft_strjoin(paths[i], "/");
	if (!tmp)
		return (NULL);
	path = ft_strjoin(tmp, cmd);
	if (!path)
		return (NULL);
	free(tmp);
	if (access(path, X_OK) == 0)
	{
		free_split(paths);
		return (path);
	}
	free(path);
	return (NULL);
}

char	*get_exec_path(char *cmd, t_data *data)
{
	char	**paths;
	int		i;
	char	*path;

	i = 0;
	if (data->min_env == 1)
		paths = ft_split(data->hidden_path, ':');
	else
		paths = ft_get_paths(&data->env);
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		path = try_access_path(cmd, paths, i);
		if (path != NULL)
			return (path);
		i++;
	}
	free_split(paths);
	return (NULL);
}

void	ft_close(void)
{
	close (0);
	close (1);
	close (2);
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
		free(path);
	}
	ft_list_clear_cmd(cmd);
	free_lenv(&data->env);
	free(data->line);
	ft_close();
	exit (1);
}

void	close_parent_fds(t_cmd *cmd)
{
	if (cmd->next)
		close(cmd->pipe_fd[1]);
	if (cmd->fd_in != -1)
		close(cmd->fd_in);
	if (cmd->fd_out != -1)
		close(cmd->fd_out);
}

void	wait_childs(t_cmd *cmd)
{
	while (cmd != NULL)
	{
		if (cmd->pid != 0)
			waitpid(cmd->pid, &g_status, 0);
		cmd = cmd->next;
	}
}

int	ft_fork(t_cmd *cmds, t_cmd *tmp, t_data *data)
{
	tmp->pid = fork ();
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
		if (tmp->next == NULL && no_fork_allowed(tmp->cmd))
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
