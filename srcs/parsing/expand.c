/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 16:13:02 by rleseur           #+#    #+#             */
/*   Updated: 2022/06/20 16:10:01 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

static char	*replace_expand(char *str, int n, char *rep, int inte)
{
	int		i;
	int		j;
	char	*n_str;

	n_str = malloc((ft_strlen(str) - (n + 1)
				+ ft_strlen(rep) + 1) * sizeof(char));
	if (!n_str)
		return (0);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && ((inte && str[i + 1] == '?')
				|| is_valid_iden(str[i + 1])))
			break ;
		n_str[i] = str[i];
	}
	j = -1;
	while (rep[++j])
		n_str[i + j] = rep[j];
	i += n;
	while (str[++i])
		n_str[i + j - (n + 1)] = str[i];
	n_str[i + j - (n + 1)] = '\0';
	return (n_str);
}

char	*make_expand(char *str, int n, t_lenv *lenv, int inte)
{
	int	size;
	int	i;

	if (inte)
		return (replace_expand(str, 1, ft_itoa(g_status), 1));
	i = -1;
	while (str[++i])
		if (str[i] == '$' && is_valid_iden(str[i + 1]))
			break ;
	while (lenv)
	{
		size = ft_strlen(lenv->k) - 1;
		if (size < n)
			size = n;
		if (ft_strncmp(&str[i + 1], lenv->k, size) == 0)
			break ;
		lenv = lenv->next;
	}
	if (!lenv)
		return (replace_expand(str, n, "", 0));
	return (replace_expand(str, n, lenv->v, 0));
}

static void	prepare_expand(char	**av, t_lenv *lenv)
{
	int		i;
	int		j;
	int		k;
	int		inte;
	char	*str;

	if ((*av)[0] == '\'')
		return ;
	j = 0;
	while (there_are_expand(&(*av)[j]))
	{
		inte = 0;
		i = -1;
		k = get_k_n(*av, &i, &inte);
		if (k > 0 || inte)
		{
			str = make_expand(*av, k, lenv, inte);
			free(*av);
			*av = str;
		}
		j = i;
		if (j >= (int)ft_strlen(*av) - 1)
			break ;
	}
}

t_cmd	*get_expands(t_cmd *cmd, t_lenv *lenv)
{
	int		i;
	t_cmd	*rt;

	rt = cmd;
	while (cmd)
	{
		i = -1;
		if (cmd->cmd)
			while (cmd->cmd[++i])
				prepare_expand(&cmd->cmd[i], lenv);
		cmd = cmd->next;
	}
	return (rt);
}
