/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 19:40:23 by aasli             #+#    #+#             */
/*   Updated: 2022/04/28 17:08:40 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../libft/libft.h"

int	check_env_var(char **env, char *var)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	**unset_var_env(char ***env, char *var, int n)
{
	int		i;
	int		j;
	int		size;
	char	**tmp;
	char	**r;

	i = 0;
	j = 0;
	size = env_size(*env);
	tmp = ft_calloc(sizeof(char *), size);
	if (!tmp)
		return (NULL);
	r = *env;
	while (r[i])
	{
		if ((ft_strncmp(r[i], var, n) != 0))
		{
			tmp[j] = ft_strdup(r[i]);
			i++;
			j++;
		}
		else
			i++;
	}
	tmp[j] = 0;
	free_env(r);
	return (tmp);
}
