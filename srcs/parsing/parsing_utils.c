/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 21:49:09 by rleseur           #+#    #+#             */
/*   Updated: 2022/06/22 18:15:07 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	check_status(t_regroup *reg, t_cmd *cmd)
{
	if (g_status == 42)
	{
		ft_list_clear_reg(reg, 1);
		if (cmd)
			ft_list_clear_cmd(cmd, 0);
		g_status = 130;
		return (0);
	}
	return (1);
}

t_regroup	*free_and_pass(t_regroup *reg, int redir)
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

t_regroup	*make_redir(t_regroup *reg, int *fd_in, int *fd_out,
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
