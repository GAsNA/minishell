/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 19:40:23 by aasli             #+#    #+#             */
/*   Updated: 2022/04/28 18:20:04 by aasli            ###   ########.fr       */
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

/*
char	**rep_var_env(char **env, char *var, char *str, int n)
{
	int		i;
	int		size;
	char	**tmp;

	i = 0;
	size = env_size(env) + 1;
	tmp = malloc(sizeof(char *) * size);
	if (!tmp)
		return (NULL);
	while (env[i])
	{
		if ((ft_strncmp(env[i], str, n) == 0))
			tmp[i] = ft_strdup(var);
		else
			tmp[i] = ft_strdup(env[i]);
		i++;
	}
	tmp[i] = 0;
	free_env(env);
	return (tmp);
}
*/

int	add_var_env(t_lenv **env, char *var)
{
	ft_addback_lenv(env, ft_new_lenv(var));
	return (1);
}

/*
char	**add_var_env(char **env, char *var)
{
	int		i;
	int		size;
	char	**tmp;

	i = 0;
	size = env_size(env) + 2;
	tmp = malloc(sizeof(char *) * size);
	if (!tmp)
		return (NULL);
	while (env[i])
	{
		tmp[i] = ft_strdup(env[i]);
		i++;
	}
	tmp[i] = ft_strdup(var);
	i++;
	tmp[i] = 0;
	free_env(env);
	return (tmp);
}*/

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

/*
char	**get_env(char **env)
{
	int		i;
	int		size;
	char	**tmp;

	i = 0;
	size = env_size(env) + 1;
	tmp = malloc(sizeof(char *) * size);
	if (!tmp)
		return (NULL);
	while (env[i])
	{
		tmp[i] = ft_strdup(env[i]);
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}*/
