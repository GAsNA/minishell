/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:37:38 by aasli             #+#    #+#             */
/*   Updated: 2022/06/10 17:29:59 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/builtins.h"
#include "../libft/libft.h"

static void	make_export(t_data *data, char *cmd)
{
	int		j;
	char	*k;

	j = check_key(cmd);
	k = get_key(cmd);
	if (!k)
		return ;
	if (is_bad_identifier(cmd[0]) == 1)
		printf("Rovidshell: export: %s: not a valid identifier\n",
			cmd);
	else if (check_env_con(&data->env, k) == 1 && k && c_c(k) == 1)
		con_var_env(&data->env, cmd + j + 1, k, ft_strlen(k) - 2);
	else if (k && check_env_var(&data->env, k))
		rep_var_env(&data->env, cmd + j + 1, k, ft_strlen(k));
	else if (*k)
		add_var_env(data, cmd);
	free(k);
}

int	ft_export(char **cmd, t_data *data)
{
	int		i;

	i = 1;
	if (cmd[1])
	{
		if (cmd[1][0] == '-')
			return (printf("Rovidshell: export: %s: options are not handled\n",
					cmd[1]), 1);
		while (cmd[i])
		{	
			if (is_bad_identifier(cmd[i][0]) == 1)
				printf("Rovidshell: export: %s: not a valid identifier\n",
					cmd[i]);
			make_export(data, cmd[i]);
			i++;
		}
		return (0);
	}
	else
		printf("Rovidshell: export: undefined behavior on bash posix\n");
	return (2);
}
