/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 08:44:25 by aasli             #+#    #+#             */
/*   Updated: 2022/06/19 15:24:32 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/builtins.h"
#include "../libft/libft.h"

static void	print_pwd_exception(char *buff)
{
	printf("//\n");
	free (buff);
}

static int	print_pwd(char *buff)
{
	free(buff);
	buff = calloc(2049, sizeof(char));
	if (!buff)
	{
		printf("Allocation error");
		return (-1);
	}
	getcwd(buff, 2048);
	printf("%s\n", buff);
	free (buff);
	return (0);
}

int	ft_pwd(char **cmd, t_lenv **env)
{
	char	*buff;

	if (cmd[1] && cmd[1][0] == '-')
	{
		buff = ft_strdjoin("Rovidshell: pwd: ", cmd[1],
				": options are not handled\n");
		if (!buff)
			return (-1);
		write(2, buff, ft_strlen(buff));
		free(buff);
		return (1);
	}
	buff = get_var_from_env(env, "PWD=", 4);
	if (!buff)
		return (2);
	else if (ft_strcmp(buff, "//") == 0)
		print_pwd_exception(buff);
	else
		if (print_pwd(buff) == 1)
			return (1);
	return (0);
}
