/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 08:50:21 by aasli             #+#    #+#             */
/*   Updated: 2022/05/04 12:38:02 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
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

	tmp = get_var_from_env(env, "PWD=", 4);
	if (tmp && get_line(env, "PWD=", 4) != -1)
	{
		rep_var_env(env, pwd, "PWD=", 4);
	}
	else
	{
		add_var_env(env, pwd);
	}
	free (tmp);
	tmp = get_var_from_env(env, "PWD=", 4);
	free (tmp);
	return (1);
}

int	update_old_pwd(t_lenv **env)
{
	char	*tmp;
	char	*tmp2;
	char	*last;

	tmp = ft_calloc(2049, sizeof(char));
	getcwd(tmp, 2048);
	tmp2 = get_var_from_env(env, "OLDPWD=", 7);
	last = ft_strjoin("OLDPWD=", tmp);
	if (tmp2 && get_line(env, "OLDPWD=", 7) != -1)
	{
		rep_var_env(env, tmp2, "OLDPWD=", 7);
	}
	else
	{
		add_var_env(env, tmp2);
	}
	free (tmp2);
	tmp2 = get_var_from_env(env, "OLDPWD=", 7);
	free (tmp);
	free (tmp2);
	free (last);
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
			if (chdir(cmd[1]) == -1)
				return (1);
			update_old_pwd(env);
			update_pwd(env, "//");
			return (0);
		}
		if (chdir(cmd[1]) == -1)
			return (1);
		update_env(env);
	}
	else if (cmd[0])
		go_home(env, get_var_from_env(env, "HOME=", 5));
	return (0);
}
