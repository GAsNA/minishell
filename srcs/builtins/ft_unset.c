/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:16:35 by aasli             #+#    #+#             */
/*   Updated: 2022/04/29 15:12:18 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../libft/libft.h"

static int	is_bad_specifier(char c)
{
	if (isalpha(c) || c == '_')
		return (0);
	return (1);
}

int	ft_unset(char **cmd, t_lenv **env)
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
			if (is_bad_specifier(cmd[i][0]) == 1)
			{
				printf("Rovidshell: unset: %s: not a valid identifier\n",
					cmd[i]);
			}
			else if (check_env_var(env, cmd[i]) == 1)
				unset_var_env(env, cmd[i], ft_strlen(cmd[i]));
			i++;
		}
		return (0);
	}
	return (2);
}
