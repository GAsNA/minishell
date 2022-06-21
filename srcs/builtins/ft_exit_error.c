/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:41:28 by aasli             #+#    #+#             */
/*   Updated: 2022/06/21 17:05:07 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/builtins.h"
#include "../libft/libft.h"
#include <limits.h>

extern int	g_status;

int	no_exit_in_error(char **cmd, int fork)
{
	if (cmd[0] && cmd[1] && cmd[2] && ft_is_integer(cmd[1]))
	{
		if (fork == 0)
			write(2, "exit\nRovidshell: exit: too many arguments\n",
				ft_strlen("Exit\nRovidshell: exit: too many arguments\n"));
		else
			write(2, "Rovidshell: exit: too many arguments\n",
				ft_strlen("Rovidshell: exit: too many arguments\n"));
		g_status = 1;
		return (1);
	}
	return (0);
}

int	exit_in_error(char **cmd, t_data *data, t_cmd *cmds, int fork)
{
	char	*tmp;

	if (cmd[0] && cmd[1] && ft_is_integer(cmd[1]) == 0)
	{
		if (fork == 1)
			tmp = ft_strdjoin("Rovidshell: exit:", cmd[1],
					": numeric argument is required\n");
		else
			tmp = ft_strdjoin("exit\nRovidshell: exit:", cmd[1],
					": numeric argument is required\n");
		if (!tmp)
			return (-1);
		write (2, tmp, ft_strlen(tmp));
		free_all(data, cmds);
		return (2);
	}
	return (0);
}
