/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 08:44:25 by aasli             #+#    #+#             */
/*   Updated: 2022/04/25 12:26:16 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../libft/libft.h"

static void	print_pwd_exception(char *buff)
{
	printf("//\n");
	free (buff);
}

static void	print_pwd(char *buff)
{
	getcwd(buff, 2048);
	printf("%s\n", buff);
	free (buff);
}

int	ft_pwd(char **cmd, char ***env)
{
	char	*buff;

	if (cmd[1] && cmd[1][0] == '-')
	{
		printf("Rovidshell: pwd: %s: options are not handled\n", cmd[1]);
		return (1);
	}
	buff = get_var_from_env(*env, "PWD=", 4);
	if (!buff)
		return (1);
	if (ft_strncmp(buff, "//", 2) == 0)
		print_pwd_exception(buff);
	else
	{
		free(buff);
		buff = calloc(2049, sizeof(char));
		if (!buff)
		{
			printf("Allocation error");
			return (1);
		}
		print_pwd(buff);
	}
	return (0);
}
