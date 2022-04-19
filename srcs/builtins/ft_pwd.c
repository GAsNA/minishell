/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 08:44:25 by aasli             #+#    #+#             */
/*   Updated: 2022/04/19 11:46:09 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../libft/libft.h"

int	ft_pwd(char **cmd)
{
	char	*buff;

	if (cmd[1] && cmd[1][0] == '-')
	{
		printf("Rovidshell: pwd: %s: options are not handled", cmd[1]);
		return (1);
	}
	buff = calloc(2049, sizeof(char));
	if (!buff)
	{
		printf("Allocation error");
		return (1);
	}
	getcwd(buff, 2048);
	printf("PWD: --- %s\n", buff);
	free(buff);
	return (0);
}
