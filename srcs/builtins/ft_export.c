/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:37:38 by aasli             #+#    #+#             */
/*   Updated: 2022/05/04 15:22:02 by aasli            ###   ########.fr       */
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
	printf("NOT NULL\n");
	tmp = ft_substr(key, 0, i);
	return (tmp);	
}

int	ft_export(char **cmd, t_lenv **env)
{
	int		i;

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
			if (is_bad_identifier(cmd[i][0]) == 1)
			{
				printf("Rovidshell: unset: %s: not a valid identifier\n",
					cmd[i]);
			}
			else if (check_env_var(env, get_key(cmd[i])) == 1 && get_key(cmd[i]) != NULL)
			{
				printf("rep\n");
				rep_var_env(env, get_key(cmd[i]), cmd[i], ft_strlen(cmd[i]));
				cmd[i] = cmd[i] + ft_strnlen(cmd[i]);
			}
			else if (get_key(cmd[i]) != NULL)
				add_var_env(env, cmd[i]);
			i++;
		}
		return (0);
	}
	return (2);
}
