/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 12:11:42 by aasli             #+#    #+#             */
/*   Updated: 2022/04/19 16:33:00 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../libft/libft.h"

int	check_cd_access(char **cmd)
{
	int	open;
	int	perm;
	DIR	*dir;

	dir = opendir(cmd[1]);
	perm = access(cmd[1], X_OK);
	open = access(cmd[1], F_OK);
	if (dir == NULL && open != -1)
	{
		printf("Rovidshell: cd: %s: Not a directory\n", cmd[1]);
		closedir(dir);
		return (1);
	}
	if (open != -1)
	{
		printf("Rovidshell: cd: %s: No such file or directory\n", cmd[1]);
		return (1);
	}
	if (perm == -1)
	{
		printf("Rovidshell: cd: %s: Permission denied\n", cmd[1]);
		return (1);
	}
	return (0);
}

int	get_line(char **env, char *str, int n)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if ((strncmp(env[i], str, n)) == 0)
			return (i);
		i++;
	}
	return (-1);
}
