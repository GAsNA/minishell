/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 12:10:30 by aasli             #+#    #+#             */
/*   Updated: 2022/05/04 12:44:18 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../libft/libft.h"

int	ft_env(char **cmd, char ***env)
{
	int		i;
	char	**tmp;

	tmp = *env;
	i = 0;
	if (cmd[1])
	{
		printf("Rovidshell: env: %s: options or arguments are not handled\n",
			cmd[1]);
		return (1);
	}
	while (tmp[i])
	{
		printf("%s\n", tmp[i]);
		i++;
	}
	return (0);
}
