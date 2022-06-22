/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:16:35 by aasli             #+#    #+#             */
/*   Updated: 2022/06/22 12:41:17 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/builtins.h"
#include "../libft/libft.h"

static int	print_unset_error(char *s1, char *s2, char *s3)
{
	char	*tmp;

	tmp = ft_strdjoin(s1, s2, s3);
	if (!tmp)
		return (1);
	write(2, tmp, ft_strlen(tmp));
	free(tmp);
	return (1);
}

int	is_bad_identifier(char c)
{
	if (isalpha(c) || c == '_' || c == '#')
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
			status = print_unset_error("Rovidshell: unset: '", cmd[i],
					"': not a valid identifier\n");
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
			print_unset_error("Rovidshell: unset: '", cmd[1],
				"': options are not handled\n");
			return (2);
		}
		status = proceed_unset(cmd, env);
	}
	return (status);
}
