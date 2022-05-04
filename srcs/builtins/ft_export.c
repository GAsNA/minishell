/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:37:38 by aasli             #+#    #+#             */
/*   Updated: 2022/05/04 17:04:20 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../libft/libft.h"

static int	is_bad_identifier(char c)
{
	if (isalpha(c) || c == '_')
		return (0);
	return (1);
}

static int	check_key(char *key)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if (key[i] == '=')
			break;
		i++;
	}
	if (i >= (int)ft_strlen(key))
		return (-1);
	return (i);	
}

static char	*get_key(char *key)
{
	int	i;
	int	j;
	char	*tmp;

	i = 0;
	j = 0;
	while (key[i])
	{
		if (key[i] == '=')
			break;
		i++;
	}
	if (i >= (int)ft_strlen(key))
		return (NULL);
	tmp = ft_substr(key, 0, i + 1);
	return (tmp);	
}

int	ft_export(char **cmd, t_lenv **env)
{
	int		i;
	int		j;
	char	*k;

	i = 1;
	if (cmd[1])
	{
		if (cmd[1][0] == '-')
		{
			printf("Rovidshell: unset: %s: options are not handled\n", cmd[1]);
			return (1);
		}
		while (cmd[i])
		{
			j = check_key(cmd[i]);
			k = get_key(cmd[i]);
			if (!k)
			{
				i++;
				continue;
			}
			if (is_bad_identifier(cmd[i][0]) == 1)
				printf("Rovidshell: unset: %s: not a valid identifier\n",
					cmd[i]);
			else if (check_env_var(env, k) == 1 && k)
				rep_var_env(env, cmd[i] + j + 1, k, ft_strlen(cmd[i]));
			else if (k != NULL)
				add_var_env(env, cmd[i]);
			free(k);
			i++;
		}
		return (0);
	}
	return (2);
}
