/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 19:40:23 by aasli             #+#    #+#             */
/*   Updated: 2022/04/29 14:59:22 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../libft/libft.h"

int	check_env_var(t_lenv **env, char *var)
{
	t_lenv *tmp;

	tmp = *env;
	if (!tmp)
		return (0);
	while (tmp)
	{
		if (ft_strncmp(tmp->k, var, ft_strlen(var)) == 0)
		{
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	unset_var_env(t_lenv **env, char *var, int n)
{
	t_lenv	*tmp;
	t_lenv	*pre;
	t_lenv	*next;
	int		i;
	int		j;

	tmp = *env;
	i = 0;
	j = 0;
	while (tmp)
	{
		if ((ft_strncmp(tmp->k, var, n) == 0))
		{
			next = tmp->next;
			break ;
		}
		tmp = tmp->next;
		i++;
	}
	if (i != 0)
	{
		tmp = *env;
		while (j < i - 1)
		{
			tmp = tmp->next;
			j++;
		}
		pre = tmp;
		tmp = tmp->next;
		free(tmp->k);
		free(tmp->v);
		free(tmp);
		pre->next = next;
	}
	return (1);
}
