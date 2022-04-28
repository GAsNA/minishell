/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 19:40:23 by aasli             #+#    #+#             */
/*   Updated: 2022/04/28 13:52:04 by aasli            ###   ########.fr       */
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
