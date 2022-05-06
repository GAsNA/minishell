/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 12:10:30 by aasli             #+#    #+#             */
/*   Updated: 2022/05/06 11:03:51 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../libft/libft.h"

int	ft_env(char **cmd, t_lenv **env)
{
	t_lenv	*tmp;

	tmp = *env;
	if (cmd[1])
	{
		printf("Rovidshell: env: %s: options or arguments are not handled\n",
			cmd[1]);
		return (1);
	}
	while (tmp)
	{
		printf("%s%s\n", tmp->k, tmp->v);
		tmp = tmp->next;
	}
	return (0);
}
