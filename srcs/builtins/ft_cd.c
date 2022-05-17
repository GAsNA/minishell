/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 08:50:21 by aasli             #+#    #+#             */
/*   Updated: 2022/05/17 13:47:12 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/builtins.h"
#include "../libft/libft.h"

char	*get_var_from_env(t_lenv **env, char *str, size_t n)
{
	t_lenv	*lst;
	char	*tmp;

	lst = *env;
	tmp = NULL;
	while (lst)
	{
		if ((strncmp(lst->k, str, n)) == 0)
		{
			tmp = ft_strdup(lst->v);
			break ;
		}
		lst = lst->next;
	}
	return (tmp);
}

int	update_pwd(t_lenv **env, char *pwd)
{
	char	*tmp;
	char	*tmp2;

	(void)pwd;
	tmp = ft_calloc(2049, sizeof(char));
	if (!tmp)
	{
		printf("Allocation error");
		return (0);
	}
	getcwd(tmp, 2048);
	tmp2 = get_var_from_env(env, "PWD=", 4);
	if (tmp2 && get_line(env, "PWD=", 4) != -1)
	{
		rep_var_env(env, tmp, "PWD=", 4);
	}
	free (tmp);
	free (tmp2);
	return (1);
}

int	update_old_pwd(t_lenv **env)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_calloc(2049, sizeof(char));
	if (!tmp)
	{
		printf("Allocation error");
		return (0);
	}
	getcwd(tmp, 2048);
	tmp2 = get_var_from_env(env, "OLDPWD=", 7);
	if (tmp2 && get_line(env, "OLDPWD=", 7) != -1)
		rep_var_env(env, tmp, "OLDPWD=", 7);
	free (tmp);
	free (tmp2);
	return (1);
}

int	ft_cd(char **cmd, t_lenv **env)
{
	if (cmd[0] && cmd[1] && cmd[2])
	{
		printf("Rovidshell: cd: too many arguments\n");
		return (1);
	}
	if (cmd[0] && cmd[1])
	{
		if (check_cd_access(cmd) == 1)
			return (1);
		if (strcmp(cmd[1], "//") == 0)
		{
			update_old_pwd(env);
			if (chdir(cmd[1]) == -1)
				return (1);
			update_pwd(env, "//");
			return (0);
		}
		update_old_pwd(env);
		if (chdir(cmd[1]) == -1)
			return (1);
		update_pwd(env, "PWD");
	}
	else if (cmd[0])
		go_home(env, get_var_from_env(env, "HOME=", 5));
	return (0);
}
