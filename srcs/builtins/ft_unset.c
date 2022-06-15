/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:16:35 by aasli             #+#    #+#             */
/*   Updated: 2022/06/15 17:31:55 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/builtins.h"
#include "../libft/libft.h"

int	is_bad_identifier(char c)
{
	if (isalpha(c) || c == '_')
		return (0);
	return (1);
}

static int	proceed_unset(char **cmd, t_lenv **env)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	while (cmd[i])
	{
		if (is_bad_identifier(cmd[i][0]) == 1)
		{
			printf("Rovidshell: unset: %s: not a valid identifier\n",
				cmd[i]);
			status = 1;
		}
		else if (check_env_var(env, cmd[i]) == 1)
			unset_var_env(env, cmd[i], ft_strlen(cmd[i]));
		i++;
	}
	return (status);
}

int	ft_unset(char **cmd, t_lenv **env)
{
	int		status;

	status = 0;
	if (cmd[1])
	{
		if (cmd[1][0] == '-')
		{
			printf("Rovidshell: unset: %s: options are not handled\n", cmd[1]);
			return (1);
		}
		status = proceed_unset(cmd, env);
/*
		while (cmd[i])
		{
			if (is_bad_identifier(cmd[i][0]) == 1)
			{
				printf("Rovidshell: unset: %s: not a valid identifier\n",
					cmd[i]);
				status = 1;
			}
			else if (check_env_var(env, cmd[i]) == 1)
				unset_var_env(env, cmd[i], ft_strlen(cmd[i]));
			i++;
		}
*/
	}
	return (status);
}
