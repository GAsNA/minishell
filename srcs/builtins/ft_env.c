/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 12:10:30 by aasli             #+#    #+#             */
/*   Updated: 2022/06/22 11:16:00 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/builtins.h"
#include "../libft/libft.h"

static int	print_env_error(char *s1, char *s2, char *s3)
{
	char *tmp;

	tmp = ft_strdjoin(s1, s2, s3);
	if (!tmp)
		return (1);
	write(2, tmp, ft_strlen(tmp));
	free(tmp);
	return (1);
}

int	ft_env(char **cmd, t_lenv **env)
{
	t_lenv	*tmp;

	tmp = *env;
	if (cmd[1])
	{
		print_env_error("Rovidshell: env: '", cmd[1],
							"': options or arguments are not handled\n");
		return (125);
	}
	while (tmp)
	{
		printf("%s%s\n", tmp->k, tmp->v);
		tmp = tmp->next;
	}
	return (0);
}
