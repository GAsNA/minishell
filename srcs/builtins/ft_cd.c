/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 08:50:21 by aasli             #+#    #+#             */
/*   Updated: 2022/04/13 11:22:24 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

int	ft_cd(char **cmd, char **env)
{
	int	access;

	if (cmd[0] && cmd[1] && cmd[2])
	{
		printf("Rovidshell: cd: too many arguments\n");
		return (1);
	}
	// Check the access of directory
	// Dup the current pwd into the old pwd
	// Use chdir
	// Set the pwd variable to this new directory
	if (cmd[0] && cmd[1])
	{
		chdir(cmd[1]);
	}
	return (0);
}
