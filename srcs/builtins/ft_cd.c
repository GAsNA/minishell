/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 08:50:21 by aasli             #+#    #+#             */
/*   Updated: 2022/04/18 22:25:49 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../libft/libft.h"

int	check_cd_access(char **cmd)
{
	int	ret;

	if ((ret = access(cmd[1], F_OK) == -1))
	{
		printf("Rovidshell: cd: %s: No such file or directory\n", cmd[1]);
		return (1);
	}
	if ((ret = access(cmd[1], X_OK) == -1))
	{
		printf("Rovidshell: cd: %s: Permission denied\n", cmd[1]);
		return (1);
	}
	return (0);
}

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
			printf("%s: %s\n", str, tmp);
			break ;
		}
		i++;
	}
	return (tmp);
}

int	get_line(char **env, char *str, int n)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if ((strncmp(env[i], str, n)) == 0)
			return (i) ;
		i++;
	}
	return (-1);
}

char **update_pwd(char **env, char *pwd)
{
	char *tmp;
	char *last;

	tmp = get_var_from_env(env, "PWD=", 4);	
	last = ft_strjoin("PWD=", pwd);
	printf("LAST ------ %s\n", last);
	if (tmp && get_line(env, "PWD=", 4) != -1)
	{
		printf("PWD exists\n");
		env = rep_var_env(env, last, "PWD=", 4);
	}
	else
	{
		printf("PWD doesn't exists\n");
		env = add_var_env(env, last);
	}
	free (tmp);
	tmp = get_var_from_env(env, "PWD=", 4);	
	printf("NEWPWD ------ %s\n", tmp);
	free (tmp);
	free (last);
	printf("-------------------------\n");
	return (env);
}


char	**update_old_pwd(char **env)
{
	char *tmp;
	char *tmp2;
	char *last;

	tmp = get_var_from_env(env, "PWD=", 4);	
	tmp2 = get_var_from_env(env, "OLDPWD=", 7);	
	last = ft_strjoin("OLDPWD=", tmp);
	if (tmp2 && get_line(env, "OLDPWD=", 7) != -1)
	{
		printf("OLDPWD exists\n");
		env = rep_var_env(env, last, "OLDPWD=", 7);
	}
	else
	{
		printf("OLDPWD doesn't exists\n");
		env = add_var_env(env, last);
	}
	free (tmp2);
	tmp2 = get_var_from_env(env, "OLDPWD=", 7);	
	free (tmp);
	free (tmp2);
	free (last);
	printf("-------------------------\n");
	return (env);
}

int	ft_cd(char **cmd, char **env)
{
	(void)env;
	if (cmd[0] && cmd[1] && cmd[2])
	{
		printf("Rovidshell: cd: too many arguments\n");
		return (1);
	}
	if (cmd[0] && cmd[1])
	{
		if (check_cd_access(cmd) == 1)
			return (1);
	// Use chdir
		if (chdir(cmd[1]) == -1)
			return (1);
	// Dup the current pwd into the old pwd
		env = update_old_pwd(env);	
	// Set the pwd variable to this new directory
		char *buff;
		buff = ft_calloc(2049, 1);
		getcwd(buff, 2048);
		printf("---------------%s\n", buff);
		env = update_pwd(env, buff);
		free(buff);
		int i = 0;
		while (env[i])
		{
			printf("%s\n", env[i]);
			i++;
		}
		free_env(env);
	}
	return (0);
}
