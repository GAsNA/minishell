/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 19:40:23 by aasli             #+#    #+#             */
/*   Updated: 2022/05/04 15:11:34 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../libft/libft.h"

int	env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

int	rep_var_env(t_lenv **env, char *var, char *str, int n)
{
	char	*tmp;
	t_lenv	*lst;

	lst = *env;
	while (lst)
	{
		if ((ft_strncmp(lst->k, str, n) == 0))
		{
			tmp = ft_strdup(var);
			free(lst->v);
			lst->v = tmp;
		}
		lst = lst-> next;
	}
	return (1);
}

int	add_var_env(t_lenv **env, char *var)
{
	ft_addback_lenv(env, ft_new_lenv(var));
	return (1);
}

t_lenv	*get_env(char **env)
{
	t_lenv	*lbegin;
	int		i;

	lbegin = NULL;
	i = 0;
	while (env[i])
	{
		ft_addback_lenv(&lbegin, ft_new_lenv(env[i]));
		i++;
	}
	return (lbegin);
}
