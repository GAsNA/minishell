/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_divide_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 10:58:49 by rleseur           #+#    #+#             */
/*   Updated: 2022/06/07 14:57:10 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	calcul_av(t_regroup *reg)
{
	int	i;

	i = 0;
	while (reg && ft_strcmp(reg->str, "|") != 0)
	{
		if (ft_strcmp(reg->str, "<") == 0
			|| ft_strcmp(reg->str, "<<") == 0
			|| ft_strcmp(reg->str, ">") == 0
			|| ft_strcmp(reg->str, ">>") == 0)
				reg = reg->next;
		else
			i++;
		reg = reg->next;
	}
	return (i);
}

t_regroup	*divide_cmd(t_regroup *reg, char ***av, int *fd)
{
	int	i;

	i = -1;
	while (reg && ft_strcmp(reg->str, "|") != 0)
	{
		if (reg->next && ft_strcmp(reg->str, "<<") == 0)
			*fd = make_heredoc(reg->next->str);
		if (ft_strcmp(reg->str, "<") == 0
			|| ft_strcmp(reg->str, "<<") == 0
			|| ft_strcmp(reg->str, ">") == 0
			|| ft_strcmp(reg->str, ">>") == 0)
				reg = reg->next;
		else
			(*av)[++i] = reg->str;
		reg = reg->next;
	}
	(*av)[i + 1] = 0;
	return (reg);
}
