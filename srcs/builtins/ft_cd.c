/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 08:50:21 by aasli             #+#    #+#             */
/*   Updated: 2022/04/20 21:12:11 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../libft/libft.h"

char	*get_var_from_env(char **env, char *str, size_t n)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	while (env[i])
	{
		if ((strncmp(env[i], str, n)) == 0)
		{
			tmp = strdup(&env[i][n]);
			break ;
		}
		i++;
	}
	return (tmp);
}

char	**update_pwd(char **env, char *pwd)
{
	char	*tmp;
	char	*last;

	tmp = get_var_from_env(env, "PWD=", 4);
	last = ft_strjoin("PWD=", pwd);
	if (tmp && get_line(env, "PWD=", 4) != -1)
	{
		env = rep_var_env(env, last, "PWD=", 4);
	}
	else
	{
		env = add_var_env(env, last);
	}
	free (tmp);
	tmp = get_var_from_env(env, "PWD=", 4);
	free (tmp);
	free (last);
	return (env);
}

char	**update_old_pwd(char **env)
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
		env = rep_var_env(env, last, "OLDPWD=", 7);
	}
	else
	{
		env = add_var_env(env, last);
	}
	free (tmp2);
	tmp2 = get_var_from_env(env, "OLDPWD=", 7);
	free (tmp);
	free (tmp2);
	free (last);
	return (env);
}

int	ft_cd(char **cmd, char ***env)
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
			*env = update_pwd(*env, "//");
			ft_pwd(cmd);
		}
		if (chdir(cmd[1]) == -1)
			return (1);
		update_env(env);
	}
	else if (cmd[0])
		go_home(env, get_var_from_env(*env, "HOME=", 5));
	return (0);
}
