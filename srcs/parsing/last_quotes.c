/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 11:28:39 by rleseur           #+#    #+#             */
/*   Updated: 2022/06/22 18:36:10 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count(char *cmd)
{
	int		i;
	int		count;
	char	q;

	i = -1;
	count = 0;
	q = 0;
	while (cmd[++i])
	{
		if (!q && (cmd[i] == '"' || cmd[i] == '\''))
			q = cmd[i];
		else if (cmd[i] == q)
			q = 0;
		else
			count++;
	}
	return (count);
}

char	*check_and_supp(char *cmd, int can_free)
{
	int		i;
	int		j;
	char	q;
	char	*str;

	str = malloc((count(cmd) + 1) * sizeof(char));
	if (!str)
		return (0);
	i = -1;
	j = 0;
	q = 0;
	while (cmd[++i])
	{
		if (!q && (cmd[i] == '"' || cmd[i] == '\''))
			q = cmd[i];
		else if (cmd[i] == q)
			q = 0;
		else
			str[j++] = cmd[i];
	}
	str[j] = 0;
	if (can_free)
		free(cmd);
	return (str);
}

t_cmd	*supp_useless_quotes(t_cmd *cmd)
{
	int		i;
	t_cmd	*ret;

	ret = cmd;
	while (cmd)
	{
		if (cmd->cmd)
		{
			i = -1;
			while (cmd->cmd[++i])
				cmd->cmd[i] = check_and_supp(cmd->cmd[i], 1);
		}
		cmd = cmd->next;
	}
	return (ret);
}
