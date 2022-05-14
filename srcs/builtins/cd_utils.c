/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 12:11:42 by aasli             #+#    #+#             */
/*   Updated: 2022/05/14 12:23:23 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/builtins.h"
#include "../libft/libft.h"

int	update_env(t_lenv **env)
{
	char	*buff;

	buff = NULL;
	update_old_pwd(env);
	buff = ft_calloc(2049, 1);
	getcwd(buff, 2048);
	update_pwd(env, buff);
	free(buff);
	return (0);
}

int	go_home(t_lenv **env, char *home)
{
	char	*buff;

	buff = NULL;
	if (home == NULL)
	{
		printf("Rovidshell: cd: HOME not set\n");
		return (1);
	}
	update_old_pwd(env);
	if (chdir(home) == -1)
		return (1);
	buff = ft_calloc(2049, 1);
	getcwd(buff, 2048);
	update_pwd(env, buff);
	free(buff);
	free(home);
	return (0);
}

int	check_cd_access(char **cmd)
{
	int	open;
	int	perm;
	DIR	*dir;

	dir = opendir(cmd[1]);
	if (dir == NULL)
	{
		printf("Rovidshell: cd: %s: %s\n", cmd[1], strerror(errno));
		return (1);
	}
	closedir(dir);
	open = access(cmd[1], F_OK);
	if (open == -1)
	{
		printf("Rovidshell: cd: %s: %s\n", cmd[1], strerror(errno));
		return (1);
	}
	perm = access(cmd[1], X_OK);
	if (perm == -1)
	{
		printf("Rovidshell: cd: %s: %s\n", cmd[1], strerror(errno));
		return (1);
	}
	return (0);
}

int	get_line(t_lenv **env, char *str, int n)
{
	int		i;
	t_lenv	*tmp;

	i = 0;
	tmp = *env;
	while (tmp)
	{
		if ((strncmp(tmp->k, str, n)) == 0)
			return (i);
		i++;
		tmp = tmp->next;
	}
	return (-1);
}
