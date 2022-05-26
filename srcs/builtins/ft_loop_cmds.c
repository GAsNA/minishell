#include "../../headers/minishell.h"
#include "../../headers/builtins.h"
#include "../libft/libft.h"

extern int	g_status;

void	ft_redir_pipe(t_cmd *cmd)
{
	if (pipe(cmd->pipe_fd) == -1)
		ft_putstr_fd("Error pipe\n", 1);
	else
	{
		if (cmd->next)
		{
			if (cmd->next->fd_in == -1)
				cmd->next->fd_in = cmd->pipe_fd[0];
		}
	//	if (!cmd->prev && cmd->fd_in == -1)
	//		cmd->fd_in
	}
}

void	ft_loop_cmds(t_cmd *cmds, char **env)
{
	t_cmd	*tmp;

	tmp = cmds;
	while (tmp != NULL)
	{
		if (tmp->next)
			ft_redir_pipe(tmp);
		ft_putstr_fd("Forking des familles\n", 1);
		tmp->pid = fork ();
		if (tmp->pid == 0)
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
			execve(tmp->cmd[0], tmp->cmd, env);
		}
		else if (tmp->pid != 0)
		{
			if (tmp->next)
				close(tmp->pipe_fd[1]);
			if (tmp->fd_in != -1)
				close(tmp->fd_in);
//			else
//				close(tmp->pipe_fd[0]);
			if (tmp->fd_out != -1)
				close(tmp->fd_out);
			if (tmp->next != NULL )
			{
//				dup2(tmp->pipe_fd[0], 0);
//				close(tmp->pipe_fd[0]);
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
