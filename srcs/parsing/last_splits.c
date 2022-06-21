/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_splits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:13:37 by rleseur           #+#    #+#             */
/*   Updated: 2022/06/20 16:11:13 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_quotes(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == '\'' || s[i] == '"')
			return (1);
	return (0);
}

static int	get_size(char **cmd)
{
	int		i;
	int		j;
	int		size;
	char	**split;

	size = 0;
	i = -1;
	while (cmd[++i])
	{
		if (get_quotes(cmd[i]))
			size++;
		else
		{
			split = ft_split(cmd[i], ' ');
			j = -1;
			while (split[++j])
			{
				size++;
				free(split[j]);
			}
			free(split);
		}
	}
	return (size);
}

static char	**get_cmd_after_split(char **cmd)
{
	int		i;
	int		j;
	int		k;
	char	**split;
	char	**new_cmd;

	new_cmd = malloc((get_size(cmd) + 1) * sizeof(char *));
	if (!new_cmd)
		return (0);
	i = -1;
	j = -1;
	while (cmd[++i])
	{
		if (get_quotes(cmd[i]))
			new_cmd[++j] = ft_strdup(cmd[i]);
		else
		{
			split = ft_split(cmd[i], ' ');
			k = -1;
			while (split[++k])
				new_cmd[++j] = split[k];
			free(split);
		}
	}
	new_cmd[j + 1] = 0;
	return (new_cmd);
}

t_cmd	*last_splits(t_cmd *cmd)
{
	int		i;
	char	**tmp_char;
	t_cmd	*ret;

	ret = cmd;
	while (cmd)
	{
		i = -1;
		tmp_char = get_cmd_after_split(cmd->cmd);
		i = -1;
		while (cmd->cmd[++i])
			free(cmd->cmd[i]);
		free(cmd->cmd);
		cmd->cmd = tmp_char;
		cmd = cmd->next;
	}
	return (ret);
}
