/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 19:40:23 by aasli             #+#    #+#             */
/*   Updated: 2022/06/09 18:25:35 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/builtins.h"
#include "../libft/libft.h"

int	con_var_env(t_lenv **env, char *var, char *str, int n)
{
	char	*tmp;
	t_lenv	*lst;

	lst = *env;
	while (lst)
	{
		if (ft_strncmp(lst->k, str, n) == 0)
		{
			tmp = ft_strjoin(lst->v, var);
			free(lst->v);
			lst->v = tmp;
			return (0);
		}
		lst = lst-> next;
	}
	return (1);
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

int	add_var_env(t_data *data, char *var)
{
	ft_addback_lenv(data, ft_new_lenv(var));
	return (1);
}

t_lenv	*get_env(t_data *data, char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_addback_lenv(data, ft_new_lenv(env[i])) == 0)
		{
			free_lenv(&data->env);
			exit (1);
		}
		i++;
	}
	if (data->env == NULL)
		exit (1);
	return (data->env);
}
