/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 12:56:01 by aasli             #+#    #+#             */
/*   Updated: 2022/06/13 13:05:21 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/builtins.h"
#include "../libft/libft.h"

extern int	g_status;

void	ft_close(void)
{
	close (0);
	close (1);
	close (2);
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
